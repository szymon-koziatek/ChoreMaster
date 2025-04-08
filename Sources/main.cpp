#include "../Headers/main.hpp"
#include "../Headers/logic.hpp"
#include "../Headers/render.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<Task> chores;
    int choice;
    bool running = true;

    while(running) {
        Render::displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        if(choice == 8) {
            running = false;
        } else if(choice == 2) {
            Render::showTasks(chores);
        } else if(choice >= 1 && choice <= 7) {
            Logic::handleUserChoice(choice, chores);
        } else {
            Render::printMessage("Invalid choice!");
        }
    }

    return 0;
}
