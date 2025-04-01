#pragma once
#include <vector>
#include <string>

namespace Helpers {
    template<typename T>
    std::vector<T> loadVectorFromFile(const std::string &filename);

    template <typename T>
    bool isSorted(const T* arr, size_t size);

    template<typename T>
    void printArray(const std::string &prefix, const std::vector<T> &vec);

    template<typename T>
    std::vector<T> loadVectorFromFile(const std::string &filename);
}
