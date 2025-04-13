#pragma once
#include <vector>
#include <string>
#include "config/ConfigParser.h"

namespace Helpers {
    // Szablonowe funkcje pomocnicze:

    template<typename T, typename Sorter>
     void run_mode_default(Sorter& sorter, ArrayType array_type, const std::string& algorithm);

    template<typename T, typename Sorter>
    void run_test_file(Sorter& sorter, std::vector<T>& data, const std::string& algorithm);

    // Новые методы
    template<typename T, typename Sorter>
    void run_test_new_save(
        Sorter& sorter,
        size_t size,
        ArrayType array_type,
        const std::string& algorithm,
        const std::string& filename
    );

    template<typename T, typename Sorter>
    void run_test_new_nosave(
        Sorter& sorter,
        size_t size,
        ArrayType array_type,
        const std::string& algorithm
    );

    template<typename T>
    void saveToFile(const std::vector<T>& data, const std::string& filename);

    // Wyświetla fragment tablicy z ograniczeniem elementów
    template<typename T>
    void printArray(const std::vector<T>& data);

    // Sprawdza czy tablica jest posortowana
    template<typename T>
    bool isSorted(const std::vector<T>& data);

    // Konwersja typów enum na string
    std::string arrayTypeToString(ArrayType type);
    std::string dataTypeToString(DataType type);
}