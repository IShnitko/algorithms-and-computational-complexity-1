#pragma once
#include <vector>
#include <string>

enum class ArrayType;

namespace Helpers {
    std::string arrayTypeToString(ArrayType type);

    template <typename T>
    void printArray(const std::vector<T>& data, size_t max_elements = 10); // Значение по умолчанию

    template <typename T>
    bool isSorted(const std::vector<T>& data); // Убраны лишние параметры
}
