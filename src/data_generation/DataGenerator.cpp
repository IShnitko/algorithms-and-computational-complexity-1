#include "../../include/data_generation/DataGenerator.h"
#include <algorithm>
#include <random>

template <typename T>
void generateArray(T* arr, int size, Config::ArrayType type) {
    std::random_device rd;
    std::mt19937 gen(rd());

    if constexpr (std::is_same_v<T, char>) {
        // Исправление для char
        std::uniform_int_distribution<int> dist(0, 127); // ASCII-символы
        for (int i = 0; i < size; i++) arr[i] = static_cast<char>(dist(gen));
    } else if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> dist(1, 1000);
        for (int i = 0; i < size; i++) arr[i] = dist(gen);
    } else {
        std::uniform_real_distribution<T> dist(0.0, 1.0);
        for (int i = 0; i < size; i++) arr[i] = dist(gen);
    }

    switch (type) {
        case Config::ArrayType::RANDOM:
            break;
        case Config::ArrayType::SORTED:
            std::sort(arr, arr + size);
        break;
        case Config::ArrayType::REVERSE_SORTED:
            std::sort(arr, arr + size, std::greater<T>());
        break;
        case Config::ArrayType::PARTIALLY_SORTED:
            std::sort(arr, arr + size/3);
        std::sort(arr + 2*size/3, arr + size);
        break;
        default:
            throw std::invalid_argument("Unknown array type");
    }
}

// Явные инстанциации
template void generateArray<int>(int*, int, Config::ArrayType);
template void generateArray<double>(double*, int, Config::ArrayType);
template void generateArray<char>(char*, int, Config::ArrayType);
