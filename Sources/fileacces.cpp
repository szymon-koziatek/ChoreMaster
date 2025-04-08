#include "../Headers/fileacces.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>

std::vector<Subtask> FileAccess::splitSubtasks(const std::string& subtasksString) {
    std::vector<Subtask> subtasks;
    std::stringstream ss(subtasksString);
    std::string subtaskName;
    
    while (std::getline(ss, subtaskName, ';')) {
        if (!subtaskName.empty()) {
            subtasks.push_back({subtaskName, false});
        }
    }
    return subtasks;
}

bool FileAccess::saveTasks(const std::vector<Task>& tasks, const std::string& filename) {
    try {
        std::ofstream file(filename);
        if (!file.is_open()) return false;

        file << "taskname,duedate,duetime,priority,completed,subtasks\n";
        
        for (const auto& task : tasks) {
            file << task.taskname << ","
                 << task.duedate << ","
                 << task.duetime << ","
                 << task.priority << ","
                 << (task.isCompleted ? "true" : "false") << ",";
            
            if (!task.subtasks.empty()) {
                for (size_t i = 0; i < task.subtasks.size(); ++i) {
                    file << task.subtasks[i].name << "|"
                         << (task.subtasks[i].isCompleted ? "1" : "0");
                    if (i != task.subtasks.size() - 1) file << ";";
                }
            }
            file << "\n";
        }
        
        file.close();
        return true;
    }
    catch (...) {
        return false;
    }
}

std::vector<Task> FileAccess::loadTasks(const std::string& filename) {
    std::vector<Task> tasks;
    std::ifstream file(filename);
    
    if (!file.is_open()) return tasks;

    std::string line;
    std::getline(file, line); // Skip header
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Task task;
        std::string field;

        std::getline(ss, field, ',');
        task.taskname = field;

        std::getline(ss, field, ',');
        task.duedate = field;

        std::getline(ss, field, ',');
        task.duetime = field;

        std::getline(ss, field, ',');
        task.priority = std::stoi(field);

        std::getline(ss, field, ',');
        task.isCompleted = (field == "true");

        std::getline(ss, field);
        std::vector<Subtask> subtasks;
        std::stringstream subtasksStream(field);
        std::string subtaskEntry;
        
        while (std::getline(subtasksStream, subtaskEntry, ';')) {
            size_t separator = subtaskEntry.find('|');
            if (separator != std::string::npos) {
                Subtask st;
                st.name = subtaskEntry.substr(0, separator);
                st.isCompleted = (subtaskEntry.substr(separator+1) == "1");
                subtasks.push_back(st);
            }
        }
        task.subtasks = subtasks;

        tasks.push_back(task);
    }
    
    file.close();
    return tasks;
}
