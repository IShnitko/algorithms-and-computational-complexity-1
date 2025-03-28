#pragma once
#include <string>
#include <unordered_map>
#include <stdexcept>

class Config {
public:
    // Enum types
    enum class Algorithm { QUICK_SORT, SHELL_SORT, HEAP_SORT, UNKNOWN };
    enum class DataType { INT, FLOAT, DOUBLE, CHAR, PERSON, UNKNOWN };
    enum class ArrayType { RANDOM, SORTED, REVERSE_SORTED, PARTIALLY_SORTED, UNKNOWN }; // Уберите внешний ArrayType.h
    enum class SortField { NAME, AGE, SALARY, UNKNOWN };

    // Configuration parameters
    Algorithm algorithm = Algorithm::UNKNOWN;
    DataType data_type = DataType::UNKNOWN;
    ArrayType array_type = ArrayType::UNKNOWN; // Теперь используется внутренний ArrayType
    SortField sort_field = SortField::UNKNOWN;
    size_t array_size = 0;
    std::string input_file;

    // Main parsing method
    static Config parse(const std::string& filename);

private:
    // Helper methods
    static std::string trim(const std::string& str);
    static Algorithm parseAlgorithm(const std::string& str);
    static DataType parseDataType(const std::string& str);
    static ArrayType parseArrayType(const std::string& str); // Возвращает Config::ArrayType
    static SortField parseSortField(const std::string& str);
};

class ConfigException : public std::runtime_error {
public:
    explicit ConfigException(const std::string& msg)
        : std::runtime_error("Config error: " + msg) {}
};