// DataGenerator.h
#pragma once
#include <vector>
#include "config/ConfigParser.h"

class DataGenerator {
public:
    static std::vector<int> generate(size_t size, ArrayType type);
};
