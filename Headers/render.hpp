#pragma once
#include "fileacces.hpp"

namespace Render {
    void displayMenu();
    void showTasks(const std::vector<Task>& tasks);
    void showSubtaskMenu(const Task& task);
    void printMessage(const std::string& message);
    void showPomodoroMenu();
}
