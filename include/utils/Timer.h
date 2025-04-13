#pragma once
#include <chrono>

// Klasa do mierzenia czasu wykonywania operacji
class Timer {
    std::chrono::high_resolution_clock::time_point start_time;  // Punkt czasowy początku pomiaru
public:
    void start();    // Rozpoczyna pomiar czasu
    double stop();   // Kończy pomiar i zwraca czas w milisekundach
};