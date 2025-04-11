#pragma once
#include <chrono>

class Timer {
    std::chrono::high_resolution_clock::time_point start_time;
public:
    void start();
    double stop();
};