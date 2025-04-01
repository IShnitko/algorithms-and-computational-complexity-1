#include "../include/utils/Helpers.h"
#include <fstream>
#include <stdexcept>

namespace Helpers {
    template <typename T>
    std::vector<T> loadVectorFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) throw std::runtime_error("File not found: " + filename);

        size_t size;
        file >> size;
        std::vector<T> data(size);
        for (size_t i = 0; i < size; ++i) file >> data[i];
        return data;
    }

    template <typename T>
    bool isSorted(const T* arr, size_t size) {
        for (size_t i = 0; i < size - 1; ++i) {
            if (arr[i] > arr[i + 1]) return false;
        }
        return true;
    }
    // Явные инстанциации
    template bool Helpers::isSorted<int>(const int*, size_t);
    template std::vector<int> loadVectorFromFile<int>(const std::string&);
    template std::vector<float> loadVectorFromFile<float>(const std::string&);
    template std::vector<double> loadVectorFromFile<double>(const std::string&);
    template std::vector<char> loadVectorFromFile<char>(const std::string&);
}