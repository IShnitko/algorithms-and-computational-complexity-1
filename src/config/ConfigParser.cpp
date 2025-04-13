#include "../include/config/ConfigParser.h"
#include <fstream>
#include <sstream>
#include <algorithm>

Config ConfigParser::parse(const std::string &filename) {
    // Otwarcie pliku konfiguracyjnego
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open config file");

    Config config;
    std::string line;

    // Przetwarzanie każdej linii pliku
    while (std::getline(file, line)) {
        // Usuwanie białych znaków i komentarzy
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (line.empty() || line[0] == '#') continue;

        // Podział linii na klucz i wartość
        const size_t delimiter = line.find('=');
        if (delimiter == std::string::npos) continue;

        std::string key = line.substr(0, delimiter);
        std::string value = line.substr(delimiter + 1);

        // Mapowanie wartości konfiguracyjnych
        if (key == "algorithm") {
            config.algorithm = value;  // Nazwa algorytmu
        } else if (key == "data_type") {
            // Typ danych
            if (value == "int") config.data_type = DataType::INT;
            else if (value == "float") config.data_type = DataType::FLOAT;
            else if (value == "char") config.data_type = DataType::CHAR;
            else if (value == "double") config.data_type = DataType::DOUBLE;
        } else if (key == "array_type") {
            // Typ generowanej tablicy
            if (value == "random") config.array_type = ArrayType::RANDOM;
            else if (value == "sorted") config.array_type = ArrayType::SORTED;
            else if (value == "reverse_sorted") config.array_type = ArrayType::REVERSE_SORTED;
            else if (value == "partially_sorted_33") config.array_type = ArrayType::PARTIALLY_SORTED_33;
            else if (value == "partially_sorted_66") config.array_type = ArrayType::PARTIALLY_SORTED_66;
            else if (value == "all") config.array_type = ArrayType::ALL;
        } else if (key == "input_file") {
            config.input_file = value;  // Ścieżka do pliku z danymi
        }
    }

    return config;
}