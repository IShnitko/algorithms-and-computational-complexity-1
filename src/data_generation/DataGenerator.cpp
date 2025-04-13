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

    // Generowanie danych w zależności od typu
    if constexpr (std::is_same_v<DataType, char>) {
        // Generowanie losowych znaków z zakresu 'a'-'z'
        std::uniform_int_distribution<int> dist('a', 'z');
        for (size_t i = 0; i < size; ++i) {
            data.push_back(static_cast<char>(dist(gen)));
        }
    } else if constexpr (std::is_floating_point_v<DataType>) {
        // Generowanie liczb zmiennoprzecinkowych
        std::uniform_real_distribution<DataType> dist(0.0, 10000.0);
        for (size_t i = 0; i < size; ++i) {
            data.push_back(dist(gen));
        }
    } else if constexpr (std::is_integral_v<DataType> && !std::is_same_v<DataType, bool>) {
        // Generowanie liczb całkowitych
        std::uniform_int_distribution<DataType> dist(0, 10000);
        for (size_t i = 0; i < size; ++i) {
            data.push_back(dist(gen));
        }
    } else {
        static_assert(sizeof(DataType) == 0, "Unsupported DataType");
    }

    // Modyfikacja danych zgodnie z wybranym typem tablicy
    switch(array_type) {
        case ArrayType::RANDOM:
            break;  // Brak modyfikacji dla danych losowych
        case ArrayType::SORTED:
            std::sort(data.begin(), data.end());
            break;
        case ArrayType::REVERSE_SORTED:
            std::sort(data.rbegin(), data.rend());
            break;
        case ArrayType::PARTIALLY_SORTED_33:
            if (size >= 3) {
                // Sortowanie pierwszych 33% elementów
                std::sort(data.begin(), data.begin() + size/3);
            }
            break;
        case ArrayType::PARTIALLY_SORTED_66:
            if (size >= 3) {
                // Sortowanie pierwszych 66% elementów
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
    // Wczytywanie danych z pliku
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Cannot open file: " + filename);

    size_t size;
    file >> size;  // Pierwsza wartość w pliku to rozmiar danych

    std::vector<DataType> data;
    data.reserve(size);
    DataType value;

    // Wczytywanie kolejnych wartości
    while (file >> value && data.size() < size) {
        data.push_back(value);
    }

    return data;
}

// Jawne instancje szablonu dla obsługiwanych typów
template class DataGenerator<int>;
template class DataGenerator<float>;
template class DataGenerator<double>;
template class DataGenerator<char>;
