#include <iostream>
#include <memory>
#include "algorithms/InsertionSort.h"
#include "algorithms/HeapSort.h"
#include "algorithms/QuickSort.h"
#include "config/ConfigParser.h"
#include "data_generation/DataGenerator.h"
#include "utils/Helpers.h"

template<typename T>
std::unique_ptr<SortAlgorithm<T>> create_sorter(const std::string& algorithm) {
    if (algorithm == "insertion_sort") return std::make_unique<InsertionSort<T>>();
    if (algorithm == "heap_sort") return std::make_unique<HeapSort<T>>();
    if (algorithm == "quick_sort") return std::make_unique<QuickSort<T>>();
    throw std::runtime_error("Unknown algorithm: " + algorithm);
}

template<typename T>
void process_data(const Config& config) {
    auto sorter = create_sorter<T>(config.algorithm);

    if (!config.input_file.empty()) {
        auto data = DataGenerator<T>::loadFromFile(config.input_file);
        Helpers::run_test(*sorter, data, config.algorithm);  // Теперь это работает
    } else {
        Helpers::run_benchmark<T>(*sorter, config.array_type, config.algorithm);
    }
}

int main() {
    try {
        Config config = ConfigParser::parse("../config/config.txt");

        switch (config.data_type) {
            case DataType::INT:    process_data<int>(config); break;
            case DataType::FLOAT:  process_data<float>(config); break;
            case DataType::DOUBLE: process_data<double>(config); break;
            case DataType::CHAR:   process_data<char>(config); break;
            default: throw std::runtime_error("Unsupported data type");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
