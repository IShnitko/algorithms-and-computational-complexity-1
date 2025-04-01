#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <bits/fs_fwd.h>
#include <bits/fs_path.h>

#include "algorithms/InsertionSort.h"
#include "algorithms/HeapSort.h"
#include "algorithms/QuickSort.h"
#include "config/ConfigParser.h"
#include "data_generation/DataGenerator.h"
#include "utils/Helpers.h"
#include "utils/Timer.h"

int main() {
    // Парсинг конфигурации
    Config config = ConfigParser::parse("../config/config.txt");

    // Выбор алгоритма
    std::unique_ptr<SortAlgorithm<int> > sorter;
    if (config.algorithm == "insertion_sort") {
        sorter = std::make_unique<InsertionSort<int> >();
    } else if (config.algorithm == "heap_sort") {
        sorter = std::make_unique<HeapSort<int> >();
    } else if (config.algorithm == "quick_sort") {
        sorter = std::make_unique<QuickSort<int> >();
    } else {
        std::cerr << "unknown algorithm: " << config.algorithm << std::endl;
        return 1;
    }

    // Тест на малых данных
    if (config.array_size <= 10) {
        std::vector<int> smallData = DataGenerator::generate(10, config.array_type);
        std::cout << "Original arr: ";
        Helpers::printArray(smallData);

        Timer timer;
        timer.start();
        sorter->sort(smallData); // Сортировка
        double time = timer.stop();

        std::cout << "Time: " << time << " ms" << std::endl;
        std::cout << "Sorted arr: ";
        Helpers::printArray(smallData);

        if (Helpers::isSorted(smallData)) {
            std::cout << "Check: OK" << std::endl;
        } else {
            std::cerr << "Check: Error!" << std::endl;
        }
    }

    // Тест на больших данных
    const std::vector<size_t> sizes = {10000, 20000, 40000, 80000, 160000, 320000, 640000};
    const int runs = 100;

    for (auto size: sizes) {
        double totalTime = 0.0;
        bool validation = true;

        for (int i = 0; i < runs; ++i) {
            std::vector<int> data = DataGenerator::generate(size, config.array_type);
            std::vector<int> copy = data;

            Timer timer;
            timer.start(); // Было: timer.startTimer();
            sorter->sort(data);
            double time = timer.stop(); // Было: getElapsedMillis()

            if (!Helpers::isSorted(copy)) {
                validation = false;
                break;
            }
        }

        if (!validation) {
            std::cerr << "Error encountered during sorting " << size << std::endl;
            return 1;
        }

        std::cout << "Size: " << size << "\tMean time: " << totalTime / runs << " ms" << std::endl;
    }

    return 0;
}
