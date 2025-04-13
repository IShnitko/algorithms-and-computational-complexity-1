// Główny plik programu. Punkt wejścia i zarządzanie konfiguracją.

#include <iostream>
#include <memory>
#include "algorithms/InsertionSort.h"
#include "algorithms/HeapSort.h"
#include "algorithms/QuickSort.h"
#include "config/ConfigParser.h"
#include "data_generation/DataGenerator.h"
#include "utils/Helpers.h"

// Fabryka tworząca obiekt sortowania w zależności od wybranego algorytmu
template<typename T>
std::unique_ptr<SortAlgorithm<T>> create_sorter(const std::string& algorithm) {
    // Tworzy instancję sortowania na podstawie nazwy algorytmu
    if (algorithm == "insertion_sort") return std::make_unique<InsertionSort<T>>();
    if (algorithm == "insertion_binary_sort") return std::make_unique<InsertionSort<T>>();
    if (algorithm == "heap_sort") return std::make_unique<HeapSort<T>>();
    if (algorithm == "quick_sort") return std::make_unique<QuickSort<T>>();
    throw std::runtime_error("Unknown algorithm: " + algorithm);
}

// Główna funkcja przetwarzająca dane
template<typename T>
void process_data(const Config& config) {
    auto sorter = create_sorter<T>(config.algorithm);

    if (!config.input_file.empty()) {
        // Tryb testowy: wczytaj dane z pliku i uruchom pojedynczy test
        auto data = DataGenerator<T>::loadFromFile(config.input_file);
        Helpers::run_test(*sorter, data, config.algorithm);
    } else {
        // Tryb benchmarku: generuj dane i mierz wydajność
        Helpers::run_benchmark<T>(*sorter, config.array_type, config.algorithm);
    }
}

int main() {
    try {
        // Parsuje plik konfiguracyjny
        Config config = ConfigParser::parse("../config/config.txt");

        // Wywołuje przetwarzanie dla odpowiedniego typu danych
        switch (config.data_type) {
            case DataType::INT:    process_data<int>(config); break;
            case DataType::FLOAT:  process_data<float>(config); break;
            case DataType::DOUBLE: process_data<double>(config); break;
            case DataType::CHAR:   process_data<char>(config); break;
            default: throw std::runtime_error("Unsupported data type");
        }
    } catch (const std::exception& e) {
        // Obsługa błędów
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
