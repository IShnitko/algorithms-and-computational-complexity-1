#pragma once
#include <vector>
#include <string>
#include "config/ConfigParser.h"

namespace Helpers {
    // Объявления шаблонных функций
    template<typename T, typename Sorter>
    void run_test(Sorter& sorter, std::vector<T>& data);

    template<typename T, typename Sorter>
    void run_benchmark(Sorter& sorter, ArrayType array_type);

    template<typename T>
    void printArray(const std::vector<T>& data, size_t max_elements);

    template<typename T>
    bool isSorted(const std::vector<T>& data);

    // Нешаблонные функции
    std::string arrayTypeToString(ArrayType type);
    std::string dataTypeToString(DataType type);
}