#pragma once
#include <vector>
#include "config/ConfigParser.h" // Добавлено для ArrayType

class DataGenerator {
public:
    static std::vector<int> generate(size_t size, ArrayType array_type); // Исправлен тип
};