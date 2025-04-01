#include "../include/data_generation/DataGenerator.h"
#include <random>
#include <algorithm>

std::vector<int> DataGenerator::generate(size_t size, ArrayType array_type) { // Исправлен тип
    std::vector<int> data(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1000);

    for (auto& val : data) val = dist(gen);

    switch (array_type) {
        case ArrayType::SORTED:
            std::sort(data.begin(), data.end());
        break;
        case ArrayType::REVERSE_SORTED:
            std::sort(data.rbegin(), data.rend());
        break;
        case ArrayType::PARTIALLY_SORTED:
            if (size >= 3) {
                std::sort(data.begin(), data.begin() + size / 3);
                std::sort(data.end() - size / 3, data.end());
            }
        break;
        default:
            break;
    }

    return data;
}