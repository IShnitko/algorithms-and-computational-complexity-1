#include "config/ConfigParser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;

// Trim whitespace and comments
string Config::trim(const string& str) {
    size_t start = str.find_first_not_of(" \t");
    if (start == string::npos) return "";

    size_t end = str.find_first_of("#\n", start);
    if (end == string::npos) end = str.length();

    return str.substr(start, end - start);
}

Config::Algorithm Config::parseAlgorithm(const string& str) {
    static const map<string, Algorithm> mapping = {
        {"quick_sort", Algorithm::QUICK_SORT},
        {"shell_sort", Algorithm::SHELL_SORT},
        {"heap_sort", Algorithm::HEAP_SORT}
    };

    auto it = mapping.find(str);
    if (it == mapping.end()) {
        throw ConfigException("Invalid algorithm: " + str);
    }
    return it->second;
}

Config::DataType Config::parseDataType(const string& str) {
    static const map<string, DataType> mapping = {
        {"int", DataType::INT},
        {"float", DataType::FLOAT},
        {"double", DataType::DOUBLE},
        {"char", DataType::CHAR},
        {"person", DataType::PERSON}
    };

    auto it = mapping.find(str);
    if (it == mapping.end()) {
        throw ConfigException("Invalid data_type: " + str);
    }
    return it->second;
}

Config::ArrayType Config::parseArrayType(const string& str) {
    static const map<string, ArrayType> mapping = {
        {"random", ArrayType::RANDOM},
        {"sorted", ArrayType::SORTED},
        {"reverse_sorted", ArrayType::REVERSE_SORTED},
        {"partially_sorted", ArrayType::PARTIALLY_SORTED}
    };

    auto it = mapping.find(str);
    if (it == mapping.end()) {
        throw ConfigException("Invalid array_type: " + str);
    }
    return it->second;
}

Config::SortField Config::parseSortField(const string& str) {
    static const map<string, SortField> mapping = {
        {"name", SortField::NAME},
        {"age", SortField::AGE},
        {"salary", SortField::SALARY}
    };

    auto it = mapping.find(str);
    if (it == mapping.end()) {
        throw ConfigException("Invalid sort_field: " + str);
    }
    return it->second;
}

Config Config::parse(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw ConfigException("Cannot open file: " + filename);
    }

    Config config;
    unordered_map<string, string> params;

    string line;
    while (getline(file, line)) {
        line = trim(line);
        if (line.empty()) continue;

        size_t delim_pos = line.find('=');
        if (delim_pos == string::npos) {
            throw ConfigException("Invalid line format: " + line);
        }

        string key = trim(line.substr(0, delim_pos));
        string value = trim(line.substr(delim_pos + 1));
        params[key] = value;
    }

    // Parse required parameters
    try {
        config.algorithm = parseAlgorithm(params.at("algorithm"));
        config.data_type = parseDataType(params.at("data_type"));
        config.array_type = parseArrayType(params.at("array_type"));

        if (params.count("array_size")) {
            config.array_size = stoul(params.at("array_size"));
        } else {
            throw ConfigException("Missing array_size");
        }
    } catch (const out_of_range&) {
        throw ConfigException("Missing required parameter");
    }

    // Optional parameters
    if (params.count("input_file")) {
        config.input_file = params.at("input_file");
    }

    if (params.count("sort_field")) {
        if (config.data_type != DataType::PERSON) {
            throw ConfigException("sort_field requires person data_type");
        }
        config.sort_field = parseSortField(params.at("sort_field"));
    }

    // Validate algorithm-data_type compatibility
    if (config.data_type == DataType::PERSON &&
        config.algorithm != Algorithm::QUICK_SORT) {
        throw ConfigException("Person data_type requires quick_sort");
    }

    return config;
}
