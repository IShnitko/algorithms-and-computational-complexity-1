#include "../include/data_generation/DataGenerator.h"
#include <fstream>
#include <random>
#include <algorithm>
#include <iostream>

// Generuje tablicę danych o określonym rozmiarze i typie
template<typename DataType>
std::vector<DataType> DataGenerator<DataType>::generate(size_t size, const ArrayType array_type) {
    std::vector<DataType> data;
    data.reserve(size);

    std::random_device rd;
    std::mt19937 gen(rd());

    // Logika generowania danych w zależności od typu danych
    if constexpr (std::is_same_v<DataType, char>) {
        // Generowanie losowych znaków z zakresu 'a'-'z'
        std::uniform_int_distribution<int> dist('a', 'z');
        for (size_t i = 0; i < size; ++i) {
            data.push_back(static_cast<char>(dist(gen)));
        }
    }
    else if constexpr (std::is_floating_point_v<DataType>) {
        // Generowanie liczb zmiennoprzecinkowych 0.0-10000.0
        std::uniform_real_distribution<DataType> dist(0.0, 10000.0);
        for (size_t i = 0; i < size; ++i) {
            data.push_back(dist(gen));
        }
    }
    else if constexpr (std::is_integral_v<DataType> && !std::is_same_v<DataType, bool>) {
        // Generowanie liczb całkowitych 0-10000
        std::uniform_int_distribution<DataType> dist(0, 10000);
        for (size_t i = 0; i < size; ++i) {
            data.push_back(dist(gen));
        }
    }
    else {
        static_assert(sizeof(DataType) == 0, "Nieobsługiwany typ danych");
    }

    // Modyfikacja struktury danych zgodnie z wybranym typem tablicy
    switch(array_type) {
        case ArrayType::RANDOM:
            break;  // Brak modyfikacji dla danych losowych
        case ArrayType::SORTED:
            std::sort(data.begin(), data.end());  // Sortowanie rosnące
            break;
        case ArrayType::REVERSE_SORTED:
            std::sort(data.rbegin(), data.rend()); // Sortowanie malejące
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
            throw std::invalid_argument("Nieznany typ tablicy");
    }

    return data;
}

// Tworzy dane: próbuje wczytać z pliku, w przypadku błędu generuje nowe
template<typename DataType>
std::vector<DataType> DataGenerator<DataType>::createData(
    size_t size,
    ArrayType array_type,
    const std::string& input_file
) {
    std::vector<DataType> data;

    if (!input_file.empty()) {
        try {
            // Próba wczytania danych z pliku
            data = loadFromFile(input_file);
            return data;
        }
        catch (const std::runtime_error& e) {
            std::cerr << "[WARNING] File load error '" << input_file
                      << "': " << e.what() << "\nGenerating new data...\n";
        }
        catch (const std::exception& e) {
            std::cerr << "[WARNING] File processing error '" << input_file
                      << "': " << e.what() << "\nGenerating new data...\n";
        }
        catch (...) {
            std::cerr << "[WARNING] Unknown error loading '"
                      << input_file << "'\nGenerating new data...\n";
        }
    }

    // Generowanie nowych danych jeśli wczytywanie się nie powiodło
    return generate(size, array_type);
}

// Wczytuje dane z pliku w formacie: rozmiar + wartości
template<typename DataType>
std::vector<DataType> DataGenerator<DataType>::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    size_t size;
    file >> size;  // Wczytaj rozmiar z pierwszej linii

    std::vector<DataType> data;
    data.reserve(size);
    DataType value;

    // Wczytaj elementy tablicy
    while (file >> value && data.size() < size) {
        data.push_back(value);
    }

    // Sprawdź zgodność deklarowanego i rzeczywistego rozmiaru
    if (data.size() != size) {
        throw std::runtime_error("File size mismatch");
    }

    return data;
}

// Jawne instancje szablonów dla obsługiwanych typów danych
template class DataGenerator<int>;
template class DataGenerator<float>;
template class DataGenerator<double>;
template class DataGenerator<char>;
