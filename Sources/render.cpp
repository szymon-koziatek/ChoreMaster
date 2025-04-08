#include "../Headers/render.hpp"
#include <iostream>
#include <string>

std::string getPriorityStars(int priority) {
    std::string stars;
    for(int i = 0; i < priority; ++i) {
        stars += "★";
    }
    return stars;
}

void Render::showTasks(const std::vector<Task>& tasks) {
    if(tasks.empty()) {
        printMessage("No tasks found!");
        return;
    }
    
    std::cout << "\n=== Task List ===";
    for(size_t i = 0; i < tasks.size(); ++i) {
        const auto& task = tasks[i];
        std::cout << "\nTask #" << i+1
             << "\n[" << (task.isCompleted ? "✓ " : "  ") << "] "
             << task.taskname
             << "\nDue: " << task.duedate << " " << task.duetime
             << "\nPriority: " << getPriorityStars(task.priority)
             << "\nSubtasks:";
        
        for(size_t j = 0; j < task.subtasks.size(); ++j) {
            std::cout << "\n  " << j+1 << ". [" 
                 << (task.subtasks[j].isCompleted ? "✓ " : "  ") << "] "
                 << task.subtasks[j].name;
        }
        std::cout << "\n-----------------";
    }
    std::cout << std::endl;
}

void Render::showSubtaskMenu(const Task& task) {
    std::cout << "\n=== Subtasks for '" << task.taskname << "' ===";
    for(size_t i = 0; i < task.subtasks.size(); ++i) {
        std::cout << "\n" << i+1 << ". [" 
             << (task.subtasks[i].isCompleted ? "✓ " : "  ") << "] "
             << task.subtasks[i].name;
    }
    std::cout << std::endl;
}

void Render::printMessage(const std::string& message) {
    std::cout << "\n" << message << "\n";
}

void Render::displayMenu() {
    std::cout << "\n=== ChoreMaster ==="
         << "\n1. Add New Task"
         << "\n2. List All Tasks"
         << "\n3. Save Tasks"
         << "\n4. Load Tasks"
         << "\n5. Delete Task"
         << "\n6. Toggle Task Completion"
         << "\n7. Toggle Subtask Completion"
         << "\n8. Start Pomodoro Session"
         << "\n9. Exit" << std::endl;
}

void Render::showPomodoroMenu() {
    std::cout << "\nPomodoro Technique Options:"
              << "\na. Start 25min Work Session"
              << "\nb. Start 5min Break"
              << "\nc. Start Full Pomodoro Cycle (4x25min + breaks)"
              << "\nd. Return to Main Menu" << std::endl;
}
