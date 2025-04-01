#include "../include/utils/Helpers.h"
#include <iostream>

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