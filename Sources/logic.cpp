#include "../Headers/logic.hpp"
#include "../Headers/render.hpp"
#include <iostream>

void Logic::addNewTask(std::vector<Task>& tasks) {
    Task newTask;
    newTask.isCompleted = false;
    
    std::cout << "\nEnter task name: ";
    std::getline(std::cin, newTask.taskname);
    
    std::cout << "Due date (YYYY-MM-DD): ";
    std::getline(std::cin, newTask.duedate);
    
    std::cout << "Due time (HH:MM): ";
    std::getline(std::cin, newTask.duetime);
    
    std::cout << "Priority (1-3): ";
    std::cin >> newTask.priority;
    std::cin.ignore();
    
    std::cout << "Subtasks (separate with ;): ";
    std::string subtasksInput;
    std::getline(std::cin, subtasksInput);
    newTask.subtasks = FileAccess::splitSubtasks(subtasksInput);
    
    tasks.push_back(newTask);
    Render::printMessage("Task added!");
}

void Logic::deleteTask(std::vector<Task>& tasks, int index) {
    if(index >= 0 && index < static_cast<int>(tasks.size())) {
        tasks.erase(tasks.begin() + index);
        Render::printMessage("Task deleted!");
    }
}

void Logic::markTaskCompleted(std::vector<Task>& tasks, int index) {
    if(index >= 0 && index < static_cast<int>(tasks.size())) {
        tasks[index].isCompleted = !tasks[index].isCompleted;
        Render::printMessage("Task status updated!");
    }
}

void Logic::toggleSubtaskCompletion(std::vector<Task>& tasks, int taskIndex, int subtaskIndex) {
    if(taskIndex >= 0 && taskIndex < static_cast<int>(tasks.size())) {
        auto& task = tasks[taskIndex];
        if(subtaskIndex >= 0 && subtaskIndex < static_cast<int>(task.subtasks.size())) {
            task.subtasks[subtaskIndex].isCompleted = 
                !task.subtasks[subtaskIndex].isCompleted;
            Render::printMessage("Subtask status updated!");
        }
    }
}

void Logic::handleUserChoice(int choice, std::vector<Task>& tasks) {
    const std::string filename = "chores.csv";
    int index, taskIndex, subtaskIndex;
    
    switch(choice) {
        case 1: addNewTask(tasks); break;
        case 3:
            if(FileAccess::saveTasks(tasks, filename)) {
                Render::printMessage("Tasks saved to " + filename + "!");
            }
            break;
        case 4:
            tasks = FileAccess::loadTasks(filename);
            Render::printMessage("Loaded " + std::to_string(tasks.size()) + " tasks");
            break;
        case 5:
            std::cout << "Enter task number to delete: ";
            std::cin >> index;
            std::cin.ignore();
            deleteTask(tasks, index - 1);
            break;
        case 6:
            std::cout << "Enter task number to toggle: ";
            std::cin >> index;
            std::cin.ignore();
            markTaskCompleted(tasks, index - 1);
            break;
        case 7:
            std::cout << "Enter task number: ";
            std::cin >> taskIndex;
            std::cout << "Enter subtask number: ";
            std::cin >> subtaskIndex;
            std::cin.ignore();
            toggleSubtaskCompletion(tasks, taskIndex-1, subtaskIndex-1);
            break;
    }
}
