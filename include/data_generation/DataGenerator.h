#pragma once
#include <vector>
#include <string>
#include "config/ConfigParser.h"

class DataGenerator {
public:
    static std::vector<int> generate(size_t size, ArrayType type);
    static std::vector<int> loadFromFile(const std::string& filename);
};
