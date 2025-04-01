#pragma once
#include <string>
#include <stdexcept>

enum class ArrayType { RANDOM, SORTED, REVERSE_SORTED, PARTIALLY_SORTED };
enum class DataType { INT, FLOAT, CHAR, DOUBLE };

struct Config {
    DataType data_type;
    ArrayType array_type;
    size_t array_size;
    std::string input_file;

    static Config parse(const std::string& filename);
};