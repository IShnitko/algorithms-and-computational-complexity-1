#pragma once
#include <chrono>
#include <functional>

class Timer {
    std::chrono::high_resolution_clock::time_point start;

public:
    // Для ручного замера
    void startTimer();
    double getElapsedMillis() const;

    // Универсальный замер времени выполнения
    template <typename Func, typename... Args>
    static double measureTime(Func&& func, Args&&... args) {
        auto start = std::chrono::high_resolution_clock::now();
        std::forward<Func>(func)(std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(end - start).count();
    }
};