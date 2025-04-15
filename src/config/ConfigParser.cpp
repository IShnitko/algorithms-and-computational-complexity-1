#include "config/ConfigParser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

using namespace std;

Config ConfigParser::parse(const string &filename) {
    // Otwarcie pliku konfiguracyjnego
    ifstream file(filename);
    if (!file.is_open()) throw runtime_error("Cannot open config file: " + filename);

    Config config;
    string line;

    // Przetwarzanie każdej linii pliku
    while (getline(file, line)) {
        // Usuwanie białych znaków i komentarzy
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (line.empty() || line[0] == '#') continue;

        // Podział linii na klucz i wartość
        size_t delimiter = line.find('=');
        if (delimiter == string::npos) continue;

        string key = line.substr(0, delimiter);
        string value = line.substr(delimiter + 1);

        // Parsowanie poszczególnych parametrów konfiguracyjnych
        if (key == "algorithm") {
            config.algorithm = value;  // Nazwa algorytmu sortowania
        }
        else if (key == "data_type") {
            // Typ generowanych/przetwarzanych danych
            if (value == "int") config.data_type = DataType::INT;
            else if (value == "float") config.data_type = DataType::FLOAT;
            else if (value == "char") config.data_type = DataType::CHAR;
            else if (value == "double") config.data_type = DataType::DOUBLE;
            else throw invalid_argument("Unknown data_type: " + value);
        }
        else if (key == "array_type") {
            // Typ generowanej tablicy testowej
            if (value == "random") config.array_type = ArrayType::RANDOM;
            else if (value == "sorted") config.array_type = ArrayType::SORTED;
            else if (value == "reverse_sorted") config.array_type = ArrayType::REVERSE_SORTED;
            else if (value == "partially_sorted_33") config.array_type = ArrayType::PARTIALLY_SORTED_33;
            else if (value == "partially_sorted_66") config.array_type = ArrayType::PARTIALLY_SORTED_66;
            else if (value == "all") config.array_type = ArrayType::ALL;
            else throw invalid_argument("Unknown array_type: " + value);
        }
        else if (key == "mode") {
            // Tryb pracy programu
            if (value == "default") config.mode = Mode::DEFAULT;
            else if (value == "test_file") config.mode = Mode::TEST_FILE;
            else if (value == "test_new_save") config.mode = Mode::TEST_NEW_SAVE;
            else if (value == "test_new_nosave") config.mode = Mode::TEST_NEW_NOSAVE;
            if (value == "comparative_benchmark") config.mode = Mode::COMPARATIVE_BENCHMARK;
            else throw invalid_argument("Unknown mode: " + value);
        }
        else if (key == "size") {
            // Rozmiar generowanej tablicy (tylko dla trybów testowych)
            config.size = stoi(value);
        }
        else if (key == "input_file") {
            // Ścieżka do pliku z danymi
            config.input_file = value;
        }
    }

    // Walidacja wymaganych parametrów
    if (config.mode == Mode::TEST_FILE || config.mode == Mode::TEST_NEW_SAVE) {
        if (config.input_file.empty()) {
            throw runtime_error("input_file is required for this mode");
        }
    }

    return config;
}
