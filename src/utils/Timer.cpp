#include "../include/utils/Timer.h"

void Timer::start() {
    // Rozpoczyna pomiar czasu, zapisując aktualny czas systemowy
    start_time = std::chrono::high_resolution_clock::now();
}

double Timer::stop() {
    // Kończy pomiar czasu i zwraca czas wykonania w milisekundach
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start_time).count();
}
