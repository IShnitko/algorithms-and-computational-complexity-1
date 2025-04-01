#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <numeric>
#include <cmath>
#include <config/ConfigParser.h>
#include <data_generation/DataGenerator.h>

#include "algorithms/InsertionSort.h"
#include "algorithms/HeapSort.h"
#include "algorithms/QuickSort.h"
#include "config/ConfigParser.h"
#include "data_generation/DataGenerator.h"
#include "utils/Helpers.h"
#include "utils/Timer.h"

struct BenchmarkResult {
    double avg_time;
    double median;
    double std_dev;
};

BenchmarkResult run_benchmark(SortAlgorithm<int>* sorter, size_t size, ArrayType array_type, int runs) {
    std::vector<double> times;
    times.reserve(runs);

    for (int i = 0; i < runs; ++i) {
        std::vector<int> data = DataGenerator::generate(size, array_type);
        std::vector<int> copy = data; // Copy for sorting

        Timer timer;
        timer.start();
        sorter->sort(copy);
        times.push_back(timer.stop());

        if (!Helpers::isSorted(copy)) {
            throw std::runtime_error("Sorting validation failed!");
        }
    }

    // Calculate statistics
    std::sort(times.begin(), times.end());
    double sum = std::accumulate(times.begin(), times.end(), 0.0);
    double avg = sum / runs;
    double median = times[runs/2];

    double sq_sum = std::inner_product(times.begin(), times.end(), times.begin(), 0.0);
    double std_dev = std::sqrt(sq_sum / runs - avg * avg);

    return {avg, median, std_dev};
}

int main() {
    try {
        // Parse config
        Config config = ConfigParser::parse("../config/config.txt");

        // Create sorter based on config
        std::unique_ptr<SortAlgorithm<int>> sorter;
        if (config.algorithm == "insertion_sort") {
            sorter = std::make_unique<InsertionSort<int>>();
        } else if (config.algorithm == "heap_sort") {
            sorter = std::make_unique<HeapSort<int>>();
        } else if (config.algorithm == "quick_sort") {
            sorter = std::make_unique<QuickSort<int>>();
        } else {
            throw std::runtime_error("Unknown algorithm: " + config.algorithm);
        }

        // Small test (10 elements)
        std::vector<int> small_data = DataGenerator::generate(10, config.array_type);
        std::cout << "Original array (10 elements): ";
        Helpers::printArray(small_data);

        Timer small_timer;
        small_timer.start();
        sorter->sort(small_data);
        double small_time = small_timer.stop();

        std::cout << "Sorted array: ";
        Helpers::printArray(small_data);
        std::cout << "Time for 10 elements: " << small_time << " ms\n\n";

        // Benchmark with different sizes
        const std::vector<size_t> sizes = {10000, 20000, 40000, 80000, 160000, 320000, 640000};
        const int runs = 100;

        std::cout << "Benchmark results (" << runs << " runs per size):\n";
        std::cout << "Size\tAvg Time (ms)\tMedian\tStd Dev\n";
        std::cout << "----------------------------------------\n";

        for (size_t size : sizes) {
            auto result = run_benchmark(sorter.get(), size, config.array_type, runs);
            std::cout << size << "\t" << result.avg_time << "\t"
                      << result.median << "\t" << result.std_dev << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}