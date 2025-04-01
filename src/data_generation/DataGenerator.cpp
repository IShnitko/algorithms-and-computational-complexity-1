#include "../include/data_generation/DataGenerator.h"
#include <fstream>
#include <random>
#include <algorithm>

std::vector<int> DataGenerator::generate(size_t size, ArrayType type) {
    std::vector<int> data(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 10000);

    // Base random data
    for (auto& val : data) val = dist(gen);

    // Apply sorting pattern
    switch (type) {
        case ArrayType::RANDOM:
            break;
        case ArrayType::SORTED:
            std::sort(data.begin(), data.end());
        break;
        case ArrayType::REVERSE_SORTED:
            std::sort(data.rbegin(), data.rend());
        break;
        case ArrayType::PARTIALLY_SORTED_33:
            if (size >= 3) {
                std::sort(data.begin(), data.begin() + size/3);
            }
        break;
        case ArrayType::PARTIALLY_SORTED_66:
            if (size >= 3) {
                std::sort(data.begin(), data.begin() + 2*(size/3));
            }
        break;
        default:
            throw std::invalid_argument("Unknown array type");
    }
    return data;
}

std::vector<int> DataGenerator::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Cannot open file from DataGenerator.cpp: " + filename);

    size_t size;
    file >> size;

    std::vector<int> data;
    data.reserve(size);
    int value;
    while (data.size() < size && file >> value) {
        data.push_back(value);
    }

    return data;
}