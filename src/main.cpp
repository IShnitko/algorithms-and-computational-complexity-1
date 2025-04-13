#include <iostream>
#include <memory>
#include "algorithms/InsertionSort.h"
#include "algorithms/InsertionBinarySort.h"
#include "algorithms/HeapSort.h"
#include "algorithms/QuickSort.h"
#include "config/ConfigParser.h"
#include "data_generation/DataGenerator.h"
#include "utils/Helpers.h"

template<typename T>
std::unique_ptr<SortAlgorithm<T>> create_sorter(const std::string& algorithm) {
    if (algorithm == "insertion_sort") return std::make_unique<InsertionSort<T>>();
    if (algorithm == "insertion_binary_sort") return std::make_unique<BinaryInsertionSort<T>>();
    if (algorithm == "heap_sort") return std::make_unique<HeapSort<T>>();
    if (algorithm == "quick_sort") return std::make_unique<QuickSort<T>>();
    throw std::runtime_error("Nieznany algorytm: " + algorithm);
}

int main() {
    try {
        // Wczytaj konfigurację
        Config config = ConfigParser::parse("../config/config.txt");
        
        // Wybierz typ danych na podstawie konfiguracji
        switch (config.data_type) {
            case DataType::INT: {
                auto sorter = create_sorter<int>(config.algorithm);
                switch (config.mode) {
                    case Mode::DEFAULT:
                        Helpers::run_mode_default<int>(*sorter, config.array_type, config.algorithm);
                        break;
                    case Mode::TEST_FILE: {
                        auto data = DataGenerator<int>::createData(config.size, config.array_type, config.input_file);
                        Helpers::run_test_file<int>(*sorter, data, config.algorithm);
                        break;
                    }
                    case Mode::TEST_NEW_SAVE:
                        Helpers::run_test_new_save<int>(*sorter, config.size, config.array_type, config.algorithm, config.input_file);
                        break;
                    case Mode::TEST_NEW_NOSAVE:
                        Helpers::run_test_new_nosave<int>(*sorter, config.size, config.array_type, config.algorithm);
                        break;
                }
                break;
            }
            case DataType::FLOAT: {
                auto sorter = create_sorter<float>(config.algorithm);
                switch (config.mode) {
                    case Mode::DEFAULT:
                        Helpers::run_mode_default<float>(*sorter, config.array_type, config.algorithm);
                    break;
                    case Mode::TEST_FILE: {
                        auto data = DataGenerator<float>::createData(config.size, config.array_type, config.input_file);
                        Helpers::run_test_file<float>(*sorter, data, config.algorithm);
                        break;
                    }
                    case Mode::TEST_NEW_SAVE:
                        Helpers::run_test_new_save<float>(*sorter, config.size, config.array_type, config.algorithm, config.input_file);
                    break;
                    case Mode::TEST_NEW_NOSAVE:
                        Helpers::run_test_new_nosave<float>(*sorter, config.size, config.array_type, config.algorithm);
                    break;
                }
                break;
            }
            case DataType::DOUBLE: {
                auto sorter = create_sorter<double>(config.algorithm);
                switch (config.mode) {
                    case Mode::DEFAULT:
                        Helpers::run_mode_default<double>(*sorter, config.array_type, config.algorithm);
                    break;
                    case Mode::TEST_FILE: {
                        auto data = DataGenerator<double>::createData(config.size, config.array_type, config.input_file);
                        Helpers::run_test_file<double>(*sorter, data, config.algorithm);
                        break;
                    }
                    case Mode::TEST_NEW_SAVE:
                        Helpers::run_test_new_save<double>(*sorter, config.size, config.array_type, config.algorithm, config.input_file);
                    break;
                    case Mode::TEST_NEW_NOSAVE:
                        Helpers::run_test_new_nosave<double>(*sorter, config.size, config.array_type, config.algorithm);
                    break;
                }
                break;
            }
            case DataType::CHAR: {
                auto sorter = create_sorter<char>(config.algorithm);
                switch (config.mode) {
                    case Mode::DEFAULT:
                        Helpers::run_mode_default<char>(*sorter, config.array_type, config.algorithm);
                    break;
                    case Mode::TEST_FILE: {
                        auto data = DataGenerator<char>::createData(config.size, config.array_type, config.input_file);
                        Helpers::run_test_file<char>(*sorter, data, config.algorithm);
                        break;
                    }
                    case Mode::TEST_NEW_SAVE:
                        Helpers::run_test_new_save<char>(*sorter, config.size, config.array_type, config.algorithm, config.input_file);
                    break;
                    case Mode::TEST_NEW_NOSAVE:
                        Helpers::run_test_new_nosave<char>(*sorter, config.size, config.array_type, config.algorithm);
                    break;
                }
                break;
            }
            default:
                throw std::runtime_error("Nieobsługiwany typ danych");
        }
    } 
    catch (const std::exception& e) {
        std::cerr << "Błąd: " << e.what() << std::endl;
        return 1;
    } 
    catch (...) {
        std::cerr << "Nieznany błąd!" << std::endl;
        return 1;
    }
    return 0;
}