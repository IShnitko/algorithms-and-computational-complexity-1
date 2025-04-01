#include "../include/utils/Timer.h"

void Timer::start() {
    start_time = std::chrono::high_resolution_clock::now(); // Используем новое имя
}

double Timer::stop() {
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start_time).count();
}