#include <iostream>
#include <vector>
#include <memory>
#include "algorithms/InsertionSort.h"
#include "algorithms/HeapSort.h"
#include "algorithms/QuickSort.h"
#include "config/ConfigParser.h"
#include "data_generation/DataGenerator.h"
#include "utils/Helpers.h"
#include "utils/Timer.h"

void run_file_test(SortAlgorithm<int>* sorter, const std::string& filename) {
    std::vector<int> data = DataGenerator::loadFromFile(filename);

    std::cout << "Original array (" << data.size() << " elements):\n";
    Helpers::printArray(data, 20);

    Timer timer;
    timer.start();
    sorter->sort(data);
    double time = timer.stop();

    std::cout << "Sorted array:\n";
    Helpers::printArray(data, 20);
    std::cout << "Time: " << time << " ms\n";

    if (!Helpers::isSorted(data)) {
        throw std::runtime_error("Sorting validation failed!");
    }
}

void run_benchmark(SortAlgorithm<int>* sorter, ArrayType array_type) {
    const std::vector<size_t> sizes = {10000, 20000, 40000, 80000, 160000, 320000, 640000};
    // const std::vector<size_t> sizes = {10000, 20000, 40000, 80000, 160000};
    const int runs = 100;

    std::cout << "\nBenchmark results (" << Helpers::arrayTypeToString(array_type) << "):\n";
    std::cout << "Size\tAvg Time (ms)\n";

    for (size_t size : sizes) {
        double total_time = 0;
        for (int i = 0; i < runs; ++i) {
            auto data = DataGenerator::generate(size, array_type);
            Timer timer;
            timer.start();
            sorter->sort(data);
            total_time += timer.stop();
        }
        std::cout << size << "\t" << total_time/runs << "\n";
    }
}

int main() {
    try {
        Config config = ConfigParser::parse("../config/config.txt");

        std::unique_ptr<SortAlgorithm<int>> sorter;
        if (config.algorithm == "insertion_sort") sorter = std::make_unique<InsertionSort<int>>();
        else if (config.algorithm == "heap_sort") sorter = std::make_unique<HeapSort<int>>();
        else if (config.algorithm == "quick_sort") sorter = std::make_unique<QuickSort<int>>();
        else throw std::runtime_error("Unknown algorithm");

        // File test mode
        if (!config.input_file.empty()) {
            try {
                run_file_test(sorter.get(), config.input_file);
            } catch (const std::exception& e) {
                std::cerr << "File test failed: " << e.what() << std::endl;
            }
            return 0;
        }

        // Benchmark all array types
        const std::vector<ArrayType> test_types = {
            ArrayType::RANDOM,
            ArrayType::SORTED,
            ArrayType::REVERSE_SORTED,
            ArrayType::PARTIALLY_SORTED_33,
            ArrayType::PARTIALLY_SORTED_66
        };

        std::cout << "Testing algorithm: " << config.algorithm << "\n\n";

        for (auto type : test_types) {
            run_benchmark(sorter.get(), type);
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}