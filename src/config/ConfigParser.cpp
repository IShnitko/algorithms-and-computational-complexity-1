#include "config/ConfigParser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

using namespace std;

Config ConfigParser::parse(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) throw runtime_error("Cannot open config file: " + filename);

    Config config;
    string line;

    while (getline(file, line)) {
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (line.empty() || line[0] == '#') continue;

        size_t delimiter = line.find('=');
        if (delimiter == string::npos) continue;

        string key = line.substr(0, delimiter);
        string value = line.substr(delimiter + 1);

        if (key == "algorithm") {
            config.algorithm = value;
        }
        else if (key == "data_type") {
            if (value == "int") config.data_type = DataType::INT;
            else if (value == "float") config.data_type = DataType::FLOAT;
            else if (value == "char") config.data_type = DataType::CHAR;
            else if (value == "double") config.data_type = DataType::DOUBLE;
            else throw invalid_argument("Unknown data_type: " + value);
        }
        else if (key == "array_type") {
            if (value == "random") config.array_type = ArrayType::RANDOM;
            else if (value == "sorted") config.array_type = ArrayType::SORTED;
            else if (value == "reverse_sorted") config.array_type = ArrayType::REVERSE_SORTED;
            else if (value == "partially_sorted_33") config.array_type = ArrayType::PARTIALLY_SORTED_33;
            else if (value == "partially_sorted_66") config.array_type = ArrayType::PARTIALLY_SORTED_66;
            else if (value == "all") config.array_type = ArrayType::ALL;
            else throw invalid_argument("Unknown array_type: " + value);
        }
        else if (key == "mode") {
            if (value == "default") config.mode = Mode::DEFAULT;
            else if (value == "test_file") config.mode = Mode::TEST_FILE;
            else if (value == "test_new_save") config.mode = Mode::TEST_NEW_SAVE;
            else if (value == "test_new_nosave") config.mode = Mode::TEST_NEW_NOSAVE;
            else throw invalid_argument("Unknown mode: " + value);
        }
        else if (key == "size") {
            config.size = stoi(value);
        }
        else if (key == "input_file") {
            config.input_file = value;
        }
    }

    // Валидация параметров
    if (config.mode == Mode::TEST_FILE || config.mode == Mode::TEST_NEW_SAVE) {
        if (config.input_file.empty()) {
            throw runtime_error("input_file is required for this mode");
        }
    }

    return config;
}
