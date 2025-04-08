#pragma once
#include "fileacces.hpp"
#include <vector>

namespace Logic {
    void addNewTask(std::vector<Task>& tasks);
    void deleteTask(std::vector<Task>& tasks, int index);
    void markTaskCompleted(std::vector<Task>& tasks, int index);
    void toggleSubtaskCompletion(std::vector<Task>& tasks, int taskIndex, int subtaskIndex);
    void handleUserChoice(int choice, std::vector<Task>& tasks);
}
