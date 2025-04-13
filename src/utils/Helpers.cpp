#include "../include/utils/Helpers.h"
#include <iostream>
#include <fstream>
#include <algorithms/SortAlgorithm.h>
#include <config/ConfigParser.h>
#include <data_generation/DataGenerator.h>
#include <utils/Timer.h>

namespace Helpers {
    // Funkcja testująca algorytm na nowych danych z zapisem do pliku
    template<typename T, typename Sorter>
    void run_test_new_save(
        Sorter& sorter,
        size_t size,
        ArrayType array_type,
        const std::string& algorithm,
        const std::string& filename
    ) {
        // Generowanie danych testowych
        auto data = DataGenerator<T>::generate(size, array_type);

        // Zapis danych do pliku przed sortowaniem
        saveToFile(data, filename);

        // Wyświetlanie wygenerowanej tablicy
        std::cout << "Generated array (" << typeid(T).name() << "):\n";
        printArray(data);

        // Sortowanie kopii danych
        auto data_copy = data;
        sorter.sort(data_copy);

        // Wyświetlanie posortowanej tablicy
        std::cout << "Sorted by " << algorithm << ":\n";
        printArray(data_copy);
    }

    // Funkcja testująca algorytm na nowych danych bez zapisu
    template<typename T, typename Sorter>
    void run_test_new_nosave(
        Sorter& sorter,
        size_t size,
        ArrayType array_type,
        const std::string& algorithm
    ) {
        // Generowanie danych testowych
        auto data = DataGenerator<T>::generate(size, array_type);

        // Wyświetlanie wygenerowanej tablicy
        std::cout << "Generated array (" << typeid(T).name() << "):\n";
        printArray(data);

        // Sortowanie kopii danych
        auto data_copy = data;
        sorter.sort(data_copy);

        // Wyświetlanie posortowanej tablicy
        std::cout << "Sorted by " << algorithm << ":\n";
        printArray(data_copy);
    }

    // Testowanie algorytmu na danych wczytanych z pliku
    template<typename T, typename Sorter>
    void run_test_file(Sorter &sorter, std::vector<T> &data, const std::string& algorithm) {
        // Wyświetlanie oryginalnej tablicy
        std::cout << "Original array (" << data.size() << " elements):\n";
        printArray(data);

        // Pomiar czasu sortowania
        Timer timer;
        timer.start();
        sorter.sort(data);
        double time = timer.stop();

        // Wyświetlanie posortowanej tablicy i czasu
        std::cout << "Sorted array by "<< algorithm <<":\n";
        printArray(data);
        std::cout << "Time: " << time << " ms\n";

        // Weryfikacja poprawności sortowania
        if (!isSorted(data)) {
            throw std::runtime_error("Sorting validation failed!");
        }
    }

    // Benchmark różnych rozmiarów danych i typów tablic
    template<typename T, typename Sorter>
    void run_mode_default(Sorter &sorter, ArrayType array_type, const std::string& algorithm) {
        const std::vector<size_t> sizes = {10000, 20000, 40000, 60000, 80000, 160000};
        const int runs = 100;  // Liczba powtórzeń testów

        if (array_type == ArrayType::ALL) {
            // Test wszystkich dostępnych typów tablic
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
                        // Generowanie i testowanie danych
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
            // Test wybranego typu tablicy
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

    // Wyświetlanie zawartości tablicy
    template<typename T>
    void printArray(const std::vector<T> &data) {
        std::cout << "[ ";
        for (size_t i = 0; i < data.size(); ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << "]\n";
    }

    // Sprawdzanie czy tablica jest posortowana
    template<typename T>
    bool isSorted(const std::vector<T> &data) {
        for (size_t i = 0; i < data.size() - 1; ++i) {
            if (data[i] > data[i + 1]) return false;
        }
        return true;
    }

    // Konwersja typu tablicy na string
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

    // Konwersja typu danych na string
    std::string dataTypeToString(const DataType type) {
        switch (type) {
            case DataType::INT: return "INT";
            case DataType::FLOAT: return "FLOAT";
            case DataType::DOUBLE: return "DOUBLE";
            case DataType::CHAR: return "CHAR";
            default: return "UNKNOWN DATATYPE";
        }
    }

    // Zapis tablicy do pliku
    template<typename T>
    void saveToFile(const std::vector<T>& data, const std::string& filename) {
        std::remove(filename.c_str());
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
        file << data.size() << "\n";
        for (const auto& item : data) {
            file << item << "\n";
        }
    }
}

// Jawne instancje szablonów dla obsługiwanych typów danych
template void Helpers::run_mode_default<int, SortAlgorithm<int>>(SortAlgorithm<int>&, ArrayType, const std::string&);
template void Helpers::run_mode_default<float, SortAlgorithm<float>>(SortAlgorithm<float>&, ArrayType, const std::string&);
template void Helpers::run_mode_default<double, SortAlgorithm<double>>(SortAlgorithm<double>&, ArrayType, const std::string&);
template void Helpers::run_mode_default<char, SortAlgorithm<char>>(SortAlgorithm<char>&, ArrayType, const std::string&);

template void Helpers::run_test_file<int, SortAlgorithm<int>>(SortAlgorithm<int>&, std::vector<int>&, const std::string&);
template void Helpers::run_test_file<float, SortAlgorithm<float>>(SortAlgorithm<float>&, std::vector<float>&, const std::string&);
template void Helpers::run_test_file<double, SortAlgorithm<double>>(SortAlgorithm<double>&, std::vector<double>&, const std::string&);
template void Helpers::run_test_file<char, SortAlgorithm<char>>(SortAlgorithm<char>&, std::vector<char>&, const std::string&);

template void Helpers::run_test_new_save<int, SortAlgorithm<int>>(SortAlgorithm<int>&, size_t, ArrayType, const std::string&, const std::string&);
template void Helpers::run_test_new_save<float, SortAlgorithm<float>>(SortAlgorithm<float>&, size_t, ArrayType, const std::string&, const std::string&);
template void Helpers::run_test_new_save<double, SortAlgorithm<double>>(SortAlgorithm<double>&, size_t, ArrayType, const std::string&, const std::string&);
template void Helpers::run_test_new_save<char, SortAlgorithm<char>>(SortAlgorithm<char>&, size_t, ArrayType, const std::string&, const std::string&);

template void Helpers::run_test_new_nosave<int, SortAlgorithm<int>>(SortAlgorithm<int>&, size_t, ArrayType, const std::string&);
template void Helpers::run_test_new_nosave<float, SortAlgorithm<float>>(SortAlgorithm<float>&, size_t, ArrayType, const std::string&);
template void Helpers::run_test_new_nosave<double, SortAlgorithm<double>>(SortAlgorithm<double>&, size_t, ArrayType, const std::string&);
template void Helpers::run_test_new_nosave<char, SortAlgorithm<char>>(SortAlgorithm<char>&, size_t, ArrayType, const std::string&);

template void Helpers::saveToFile<int>(const std::vector<int>&, const std::string&);
template void Helpers::saveToFile<float>(const std::vector<float>&, const std::string&);
template void Helpers::saveToFile<double>(const std::vector<double>&, const std::string&);
template void Helpers::saveToFile<char>(const std::vector<char>&, const std::string&);

template void Helpers::printArray<int>(const std::vector<int>&);
template void Helpers::printArray<float>(const std::vector<float>&);
template void Helpers::printArray<double>(const std::vector<double>&);
template void Helpers::printArray<char>(const std::vector<char>&);

template bool Helpers::isSorted<int>(const std::vector<int>&);
template bool Helpers::isSorted<float>(const std::vector<float>&);
template bool Helpers::isSorted<double>(const std::vector<double>&);
template bool Helpers::isSorted<char>(const std::vector<char>&);
