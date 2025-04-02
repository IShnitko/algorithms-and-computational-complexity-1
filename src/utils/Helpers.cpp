#include "../include/utils/Helpers.h"
#include <iostream>
#include <algorithms/SortAlgorithm.h>
#include <config/ConfigParser.h>
#include <data_generation/DataGenerator.h>
#include <utils/Timer.h>

namespace Helpers {
    template<typename T, typename Sorter>
    void run_test(Sorter &sorter, std::vector<T> &data) {
        std::cout << "Original array (" << typeid(T).name() << ", "
                << data.size() << " elements):\n";
        printArray(data, 20);

        Timer timer;
        timer.start();
        sorter.sort(data);
        double time = timer.stop();

        std::cout << "Sorted array:\n";
        printArray(data, 20);
        std::cout << "Time: " << time << " ms\n";

        if (!isSorted(data)) {
            throw std::runtime_error("Sorting validation failed!");
        }
    }

    // Обобщенный бенчмарк
    template<typename T, typename Sorter>
    void run_benchmark(Sorter &sorter, ArrayType array_type) {
        const std::vector<size_t> sizes = {10000, 20000, 40000, 80000, 160000, 320000};
        const int runs = 100;
        std::cout << "\nBenchmark results (" << arrayTypeToString(array_type)
                << "):\nSize\tAvg Time (ms)\n";

        for (size_t size: sizes) {
            double total = 0;
            for (int i = 0; i < runs; ++i) {
                auto data = DataGenerator<T>::generate(size, array_type);
                Timer timer;
                timer.start();
                sorter.sort(data);
                total += timer.stop();
            }
            std::cout << size << "\t" << total / runs << "\n";
        }
    }

    template<typename T>
    void printArray(const std::vector<T> &data, size_t max_elements) {
        std::cout << "[ ";
        for (size_t i = 0; i < std::min(data.size(), max_elements); ++i) {
            std::cout << data[i] << " ";
        }
        if (data.size() > max_elements) std::cout << "...";
        std::cout << "]\n";
    }

    template<typename T>
    bool isSorted(const std::vector<T> &data) {
        for (size_t i = 0; i < data.size() - 1; ++i) {
            if (data[i] > data[i + 1]) return false;
        }
        return true;
    }
    std::string arrayTypeToString(const ArrayType type) {
        switch (type) {
            case ArrayType::RANDOM: return "RANDOM";
            case ArrayType::SORTED: return "SORTED";
            case ArrayType::REVERSE_SORTED: return "REVERSE_SORTED";
            case ArrayType::PARTIALLY_SORTED_33: return "PARTIALLY_SORTED_33";
            case ArrayType::PARTIALLY_SORTED_66: return "PARTIALLY_SORTED_66";
            default: return "UNKNOWN ARRAY TYPE";
        }
    }

    std::string dataTypeToString(const DataType type) {
        switch (type) {
            case DataType::INT: return "INT";
            case DataType::FLOAT: return "FLOAT";
            case DataType::DOUBLE: return "DOUBLE";
            case DataType::CHAR: return "CHAR";
            default: return "UNKNOWN DATATYPE";
        }
    }

}

template void Helpers::run_test<int, SortAlgorithm<int>>(SortAlgorithm<int>&, std::vector<int>&);
template void Helpers::run_test<float, SortAlgorithm<float>>(SortAlgorithm<float>&, std::vector<float>&);
template void Helpers::run_test<double, SortAlgorithm<double>>(SortAlgorithm<double>&, std::vector<double>&);
template void Helpers::run_test<char, SortAlgorithm<char>>(SortAlgorithm<char>&, std::vector<char>&);

// Явное инстанцирование для run_benchmark
template void Helpers::run_benchmark<int, SortAlgorithm<int>>(SortAlgorithm<int>&, ArrayType);
template void Helpers::run_benchmark<float, SortAlgorithm<float>>(SortAlgorithm<float>&, ArrayType);
template void Helpers::run_benchmark<double, SortAlgorithm<double>>(SortAlgorithm<double>&, ArrayType);
template void Helpers::run_benchmark<char, SortAlgorithm<char>>(SortAlgorithm<char>&, ArrayType);

// Явное инстанцирование для printArray
template void Helpers::printArray<int>(const std::vector<int>&, size_t);
template void Helpers::printArray<float>(const std::vector<float>&, size_t);
template void Helpers::printArray<double>(const std::vector<double>&, size_t);
template void Helpers::printArray<char>(const std::vector<char>&, size_t);

// Явное инстанцирование для isSorted
template bool Helpers::isSorted<int>(const std::vector<int>&);
template bool Helpers::isSorted<float>(const std::vector<float>&);
template bool Helpers::isSorted<double>(const std::vector<double>&);
template bool Helpers::isSorted<char>(const std::vector<char>&);