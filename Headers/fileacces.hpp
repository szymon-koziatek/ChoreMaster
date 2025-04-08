#pragma once
#include <vector>
#include <string>

struct Subtask {
    std::string name;
    bool isCompleted;
};

struct Task {
    std::string taskname;
    std::string duedate;
    std::string duetime;
    int priority;
    bool isCompleted;
    std::vector<Subtask> subtasks;
};

class FileAccess {
public:
    static bool saveTasks(const std::vector<Task>& tasks, const std::string& filename);
    static std::vector<Task> loadTasks(const std::string& filename);
    static std::vector<Subtask> splitSubtasks(const std::string& subtasksString);
};
