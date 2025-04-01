#include "../include/data_generation/DataGenerator.h"
#include <random>
#include <algorithm>

template <typename T>
void generateData(std::vector<T>& data, ArrayType type) {
    std::random_device rd;
    std::mt19937 gen(rd());

    if constexpr (std::is_same_v<T, char>) {
        // Генерация печатных ASCII символов (A-Z)
        std::uniform_int_distribution<int> dist('A', 'Z');
        for (auto& val : data) val = static_cast<char>(dist(gen));
    } else if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> dist(0, 1000);
        for (auto& val : data) val = dist(gen);
    } else if constexpr (std::is_floating_point_v<T>) {
        std::uniform_real_distribution<T> dist(0.0, 1000.0);
        for (auto& val : data) val = dist(gen);
    }

    switch (type) {
        case ArrayType::SORTED:
            std::sort(data.begin(), data.end());
        break;
        case ArrayType::REVERSE_SORTED:
            std::sort(data.rbegin(), data.rend());
        break;
        case ArrayType::PARTIALLY_SORTED:
            if (data.size() >= 3) {
                std::sort(data.begin(), data.begin() + data.size() / 3);
                std::sort(data.end() - data.size() / 3, data.end());
            }
        break;
        default:
            break;
    }
}

// Явные инстанциации
template void generateData<int>(std::vector<int>&, ArrayType);
template void generateData<float>(std::vector<float>&, ArrayType);
template void generateData<double>(std::vector<double>&, ArrayType);
template void generateData<char>(std::vector<char>&, ArrayType);