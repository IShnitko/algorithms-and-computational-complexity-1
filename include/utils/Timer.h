#pragma once
#include <chrono>

class Timer {
    std::chrono::high_resolution_clock::time_point start;
public:
    void startTimer();
    double getElapsedMillis() const;
};