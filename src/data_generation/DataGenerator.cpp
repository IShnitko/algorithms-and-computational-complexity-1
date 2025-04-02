#include "../include/data_generation/DataGenerator.h"
#include <fstream>
#include <random>
#include <algorithm>

template<typename DataType>
std::vector<DataType> DataGenerator<DataType>::generate(size_t size, const ArrayType array_type) {
    std::vector<DataType> data;
    data.reserve(size);

    std::random_device rd;
    std::mt19937 gen(rd());

    if constexpr (std::is_same_v<DataType, char>) {
        // Генерация символов 'a'-'z'
        std::uniform_int_distribution<int> dist('a', 'z');
        for (size_t i = 0; i < size; ++i) {
            data.push_back(static_cast<char>(dist(gen)));
        }
    } else if constexpr (std::is_floating_point_v<DataType>) {
        // Для float/double
        std::uniform_real_distribution<DataType> dist(0.0, 10000.0);
        for (size_t i = 0; i < size; ++i) {
            data.push_back(dist(gen));
        }
    } else if constexpr (std::is_integral_v<DataType> && !std::is_same_v<DataType, bool>) {
        // Для int/short/long и других целочисленных (кроме char и bool)
        std::uniform_int_distribution<DataType> dist(0, 10000);
        for (size_t i = 0; i < size; ++i) {
            data.push_back(dist(gen));
        }
    } else {
        static_assert(sizeof(DataType) == 0, "Unsupported DataType");
    }

    // Apply sorting pattern based on array_type parameter
    switch(array_type) {
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

template<typename DataType>
std::vector<DataType> DataGenerator<DataType>::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Cannot open file: " + filename);

    size_t size;
    file >> size;

    std::vector<DataType> data;
    data.reserve(size);
    DataType value;
    
    while (file >> value && data.size() < size) {
        data.push_back(value);
    }

    return data;
}
template class DataGenerator<int>;
template class DataGenerator<float>;
template class DataGenerator<double>;
template class DataGenerator<char>;
