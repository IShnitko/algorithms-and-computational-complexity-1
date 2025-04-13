#include "../include/utils/Helpers.h"
#include <iostream>
#include <algorithms/SortAlgorithm.h>
#include <config/ConfigParser.h>
#include <data_generation/DataGenerator.h>
#include <utils/Timer.h>

namespace Helpers {
    // Funkcja testująca pojedyncze sortowanie na danych z pliku
    template<typename T, typename Sorter>
    void run_test(Sorter &sorter, std::vector<T> &data, const std::string& algorithm) {
        std::cout << "Original array (" << data.size() << " elements):\n";
        printArray(data);

        Timer timer;
        timer.start();
        sorter.sort(data);  // Główna operacja sortowania
        double time = timer.stop();

        std::cout << "Sorted array by "<< algorithm <<":\n";
        printArray(data);
        std::cout << "Time: " << time << " ms\n";

        // Walidacja poprawności sortowania
        if (!isSorted(data)) {
            throw std::runtime_error("Sorting validation failed!");
        }
    }

    // Funkcja wykonująca pomiary wydajności dla różnych rozmiarów danych
    template<typename T, typename Sorter>
    void run_benchmark(Sorter &sorter, ArrayType array_type, const std::string& algorithm) {
        const std::vector<size_t> sizes = {10000, 20000, 40000, 60000, 80000, 160000};
        const int runs = 100;  // Liczba powtórzeń dla uśredniania wyników

        if (array_type == ArrayType::ALL) {
            // Test wszystkich typów tablic jeśli wybrano "ALL"
            const std::vector test_types = {
                ArrayType::RANDOM,
                ArrayType::SORTED,
                ArrayType::REVERSE_SORTED,
                ArrayType::PARTIALLY_SORTED_33,
                ArrayType::PARTIALLY_SORTED_66
            };
            for (ArrayType type : test_types) {
                std::cout << "\nBenchmark of "<< algorithm << ". Array type: (" << arrayTypeToString(type)
                << "):\nSize\tAvg Time (ms)\n";
                for (size_t size: sizes) {
                    double total = 0;
                    for (int i = 0; i < runs; ++i) {
                        auto data = DataGenerator<T>::generate(size, type);
                        Timer timer;
                        timer.start();
                        sorter.sort(data);
                        total += timer.stop();
                    }
                    std::cout << size << "\t" << total / runs << "\n";
                }
            }
        } else {
            // Test tylko wybranego typu tablicy
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
    }

    // Wyświetla elementy tablicy z ograniczeniem do max_elements
    template<typename T>
    void printArray(const std::vector<T> &data) {
        std::cout << "[ ";
        for (size_t i = 0; i < data.size(); ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << "]\n";
    }

    // Sprawdza czy tablica jest posortowana rosnąco
    template<typename T>
    bool isSorted(const std::vector<T> &data) {
        for (size_t i = 0; i < data.size() - 1; ++i) {
            if (data[i] > data[i + 1]) return false;  // Znaleziono błąd w sortowaniu
        }
        return true;
    }

    // Konwersja enum ArrayType na czytelny string
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

    // Konwersja enum DataType na czytelny string
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

// Jawne instancje szablonów dla obsługiwanych typów danych
template void Helpers::run_test<int, SortAlgorithm<int>>(SortAlgorithm<int>&, std::vector<int>&, const std::string&);
template void Helpers::run_test<float, SortAlgorithm<float>>(SortAlgorithm<float>&, std::vector<float>&, const std::string&);
template void Helpers::run_test<double, SortAlgorithm<double>>(SortAlgorithm<double>&, std::vector<double>&, const std::string&);
template void Helpers::run_test<char, SortAlgorithm<char>>(SortAlgorithm<char>&, std::vector<char>&, const std::string&);

template void Helpers::run_benchmark<int, SortAlgorithm<int>>(SortAlgorithm<int>&, ArrayType, const std::string&);
template void Helpers::run_benchmark<float, SortAlgorithm<float>>(SortAlgorithm<float>&, ArrayType, const std::string&);
template void Helpers::run_benchmark<double, SortAlgorithm<double>>(SortAlgorithm<double>&, ArrayType, const std::string&);
template void Helpers::run_benchmark<char, SortAlgorithm<char>>(SortAlgorithm<char>&, ArrayType, const std::string&);

template void Helpers::printArray<int>(const std::vector<int>&);
template void Helpers::printArray<float>(const std::vector<float>&);
template void Helpers::printArray<double>(const std::vector<double>&);
template void Helpers::printArray<char>(const std::vector<char>&);

template bool Helpers::isSorted<int>(const std::vector<int>&);
template bool Helpers::isSorted<float>(const std::vector<float>&);
template bool Helpers::isSorted<double>(const std::vector<double>&);
template bool Helpers::isSorted<char>(const std::vector<char>&);
