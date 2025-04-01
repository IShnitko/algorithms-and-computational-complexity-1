#include "../include/utils/Helpers.h"
#include <iostream>
#include <config/ConfigParser.h>

namespace Helpers {
    template <typename T>
    void printArray(const std::vector<T>& data, size_t max_elements) {
        std::cout << "[ ";
        for (size_t i = 0; i < std::min(data.size(), max_elements); ++i) {
            std::cout << data[i] << " ";
        }
        if (data.size() > max_elements) std::cout << "...";
        std::cout << "]\n";
    }

    template <typename T>
    bool isSorted(const std::vector<T>& data) {
        for (size_t i = 0; i < data.size() - 1; ++i) {
            if (data[i] > data[i + 1]) return false;
        }
        return true;
    }

    // Явные инстанциации
    template void printArray<int>(const std::vector<int>&, size_t);
    template bool isSorted<int>(const std::vector<int>&);
}

std::string Helpers::arrayTypeToString(ArrayType type) {
    switch (type) {
        case ArrayType::RANDOM: return "RANDOM";
        case ArrayType::SORTED: return "SORTED";
        case ArrayType::REVERSE_SORTED: return "REVERSE_SORTED";
        case ArrayType::PARTIALLY_SORTED_33: return "PARTIALLY_SORTED_33";
        case ArrayType::PARTIALLY_SORTED_66: return "PARTIALLY_SORTED_66";
        default: return "UNKNOWN";
    }
}
