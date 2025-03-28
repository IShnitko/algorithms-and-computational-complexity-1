#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <memory>

// Подключение заголовков проекта
#include "config/ConfigParser.h"
#include "algorithms/QuickSort.h"
// #include "algorithms/ShellSort.h"
// #include "algorithms/HeapSort.h"
#include "data_generation/DataGenerator.h"
#include "data_types/Person.h"
#include "utils/Helpers.h"
#include "utils/Timer.h"

using namespace std;

// Создание компаратора для объектов Person
function<bool(const Person&, const Person&)> createPersonComparator(Config::SortField field) {
    switch (field) {
        case Config::SortField::NAME:
            return [](const Person& a, const Person& b) { return a.name < b.name; };
        case Config::SortField::AGE:
            return [](const Person& a, const Person& b) { return a.age < b.age; };
        case Config::SortField::SALARY:
            return [](const Person& a, const Person& b) { return a.salary < b.salary; };
        default:
            throw invalid_argument("Invalid sort field");
    }
}

// Основная функция
int main() {
    try {
        // 1. Парсинг конфигурационного файла
        Config config = Config::parse("../config/config.txt");

        // 2. Генерация данных
        vector<Person> people;
        vector<int> intArr;
        vector<double> doubleArr;
        vector<char> charArr;

        switch (config.data_type) {
            case Config::DataType::PERSON:
                people = generatePeople(config.array_size, static_cast<ArrayType>(config.array_type));
                break;
            case Config::DataType::INT:
                intArr.resize(config.array_size);
                generateArray(intArr.data(), config.array_size, config.array_type);
                break;
            case Config::DataType::DOUBLE:
                doubleArr.resize(config.array_size);
                generateArray(doubleArr.data(), config.array_size, config.array_type);
                break;
            case Config::DataType::CHAR:
                charArr.resize(config.array_size);
                generateArray(charArr.data(), config.array_size, config.array_type);
                break;
            default:
                throw runtime_error("Unsupported data type");
        }

        // 3. Тестирование алгоритма
        double totalTime = 0.0;
        const int runs = 5;
        bool validation = false;

        for (int i = 0; i < runs; ++i) {
            // Создание копии данных для каждого запуска
            auto peopleCopy = people;
            auto intArrCopy = intArr;
            auto doubleArrCopy = doubleArr;
            auto charArrCopy = charArr;

            Timer timer;
            timer.startTimer();

            switch (config.algorithm) {
                case Config::Algorithm::QUICK_SORT: {
                    if (config.data_type != Config::DataType::PERSON) {
                        throw runtime_error("QuickSort supports only Person objects");
                    }
                    auto comp = createPersonComparator(config.sort_field);
                    QuickSort::sort(peopleCopy.data(), peopleCopy.size(), comp);
                    break;
                }
                // case Config::Algorithm::SHELL_SORT: {
                //     switch (config.data_type) {
                //         case Config::DataType::INT:
                //             ShellSort::sort(intArrCopy.data(), intArrCopy.size());
                //             break;
                //         case Config::DataType::DOUBLE:
                //             ShellSort::sort(doubleArrCopy.data(), doubleArrCopy.size());
                //             break;
                //         case Config::DataType::CHAR:
                //             ShellSort::sort(charArrCopy.data(), charArrCopy.size());
                //             break;
                //         default: break;
                //     }
                //     break;
                // }
                // case Config::Algorithm::HEAP_SORT: {
                //     switch (config.data_type) {
                //         case Config::DataType::INT:
                //             HeapSort::sort(intArrCopy.data(), intArrCopy.size());
                //             break;
                //         case Config::DataType::DOUBLE:
                //             HeapSort::sort(doubleArrCopy.data(), doubleArrCopy.size());
                //             break;
                //         case Config::DataType::CHAR:
                //             HeapSort::sort(charArrCopy.data(), charArrCopy.size());
                //             break;
                //         default: break;
                // }
                //     break;
                // }
                default:
                    throw runtime_error("Unknown algorithm");
            }

            totalTime += timer.getElapsedMillis();

            // Проверка корректности на первом запуске
            if (i == 0) {
                switch (config.data_type) {
                    case Config::DataType::PERSON: {
                        auto comp = createPersonComparator(config.sort_field);
                        validation = isSorted(peopleCopy.data(), peopleCopy.size(), comp);
                        break;
                    }
                    case Config::DataType::INT:
                        validation = isSorted(intArrCopy.data(), intArrCopy.size(), less<int>());
                        break;
                    case Config::DataType::DOUBLE:
                        validation = isSorted(doubleArrCopy.data(), doubleArrCopy.size(), less<double>());
                        break;
                    case Config::DataType::CHAR:
                        validation = isSorted(charArrCopy.data(), charArrCopy.size(), less<char>());
                        break;
                    default: break;
                }
            }
        }

        // 4. Вывод результатов
        cout << "\n=== Benchmark Results ==="
             << "\nAlgorithm: " << [&]{
                    switch(config.algorithm) {
                        case Config::Algorithm::QUICK_SORT: return "QuickSort";
                        case Config::Algorithm::SHELL_SORT: return "ShellSort";
                        case Config::Algorithm::HEAP_SORT: return "HeapSort";
                        default: return "Unknown";
                    }
                }()
             << "\nData type: " << [&]{
                    switch(config.data_type) {
                        case Config::DataType::PERSON: return "Person";
                        case Config::DataType::INT: return "int";
                        case Config::DataType::DOUBLE: return "double";
                        case Config::DataType::CHAR: return "char";
                        default: return "unknown";
                    }
                }()
             << "\nArray size: " << config.array_size
             << "\nArray type: " << [&]{
                    switch(config.array_type) {
                        case Config::ArrayType::RANDOM: return "Random";
                        case Config::ArrayType::SORTED: return "Sorted";
                        case Config::ArrayType::REVERSE_SORTED: return "Reverse Sorted";
                        case Config::ArrayType::PARTIALLY_SORTED: return "Partially Sorted";
                        default: return "Unknown";
                    }
                }()
             << "\nAverage time: " << totalTime / runs << " ms"
             << "\nValidation: " << (validation ? "PASSED" : "FAILED")
             << "\n========================" << endl;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}