#pragma once
#include <chrono>
#include <thread>
#include <atomic>
#include <iostream>

namespace Pomodoro {
    void startSession(int minutes);
    void startPomodoro();
    void showTimer(int seconds, bool isWorkPhase);
}
