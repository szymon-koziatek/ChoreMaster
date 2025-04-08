#include "../Headers/pomodoro.hpp"
#include <iostream>
#include <iomanip>

namespace Pomodoro {
    std::atomic<bool> timerActive(false);

    void showTimer(int seconds, bool isWorkPhase) {
        int mins = seconds / 60;
        int secs = seconds % 60;
        std::cout << "\n\033[2K\r"; // Clear entire line
        std::cout << (isWorkPhase ? "⏳ WORK TIME: " : "☕ BREAK TIME: ")
                  << std::setw(2) << std::setfill('0') << mins << ":"
                  << std::setw(2) << std::setfill('0') << secs;
        std::cout.flush();
    }

    void startSession(int minutes) {
        timerActive = true;
        int totalSeconds = minutes * 60;
        
        for(int i = totalSeconds; i > 0 && timerActive; --i) {
            showTimer(i, minutes == 25);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        
        if(timerActive) {
            std::cout << "\n\033[2K\r" 
                      << (minutes == 25 ? "Work session complete! " : "Break time over! ")
                      << "Press enter to continue...";
            std::cin.ignore();
        }
    }

    void startPomodoro() {
        timerActive = true;
        int sessionCount = 0;
        
        while(timerActive) {
            std::cout << "\nStarting work session (" << (sessionCount + 1) << "/4)";
            startSession(25);
            
            if(!timerActive) break;
            
            if(++sessionCount % 4 == 0) {
                std::cout << "\nLong break time!";
                startSession(15);
                sessionCount = 0;
            } else {
                std::cout << "\nShort break time!";
                startSession(5);
            }
        }
    }
}
