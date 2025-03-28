#include "../../include/data_generation/DataGenerator.h"
#include <random>
#include <algorithm>

template <typename T>
void generateArray(T* arr, int size, ArrayType type) {
    std::random_device rd;
    std::mt19937 gen(rd());

    if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> dist(1, 1000);
        for (int i = 0; i < size; i++) arr[i] = dist(gen);
    } else {
        std::uniform_real_distribution<T> dist(0.0, 1.0);
        for (int i = 0; i < size; i++) arr[i] = dist(gen);
    }

    // ... остальная реализация
}

// Явные инстанциации для поддержки типов
template void generateArray<int>(int*, int, ArrayType);
template void generateArray<double>(double*, int, ArrayType);

std::string arrayTypeToString(ArrayType type) {
    // ... реализация
}

std::vector<Person> generatePeople(int count, ArrayType type) {
    // ... реализация
}