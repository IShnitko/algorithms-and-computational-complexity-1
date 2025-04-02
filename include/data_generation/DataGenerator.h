#pragma once
#include <vector>
#include <string>
#include "config/ConfigParser.h"


template<typename DataType>
class DataGenerator {
public:
    static std::vector<DataType> generate(size_t size, ArrayType array_type);
    static std::vector<DataType> loadFromFile(const std::string& filename);
};
