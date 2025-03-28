#include "../../include/utils/Timer.h"

void Timer::startTimer() {
    start = std::chrono::high_resolution_clock::now();
}

double Timer::getElapsedMillis() const {
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}