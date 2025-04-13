#pragma once
#include <vector>
#include <string>
#include "config/ConfigParser.h"

// Klasa generująca dane testowe dla algorytmów sortowania
template<typename DataType>
class DataGenerator {
public:
    // Generuje tablicę według określonego typu
    static std::vector<DataType> generate(size_t size, ArrayType array_type);

    // Wczytuje dane z pliku wejściowego
    static std::vector<DataType> loadFromFile(const std::string& filename);

    // Stworzenie nowych danych o zadanym rozmiarze
    static std::vector<DataType> createData(size_t size, ArrayType array_type, const std::string& input_file = "");
};
