#pragma once
#include <string>

enum class DataType { INT, FLOAT, CHAR, DOUBLE };
enum class ArrayType { RANDOM, SORTED, REVERSE_SORTED, PARTIALLY_SORTED };

struct Config {
    std::string algorithm;
    DataType data_type;
    ArrayType array_type;
    size_t array_size = 0;
    std::string input_file;
};

class ConfigParser {
public:
    static Config parse(const std::string& filename);
};