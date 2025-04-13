#pragma once
#include <vector>
#include <string>
#include "config/ConfigParser.h"

namespace Helpers {
    // Szablonowe funkcje pomocnicze:

    // Uruchamia pojedynczy test sortowania
    template<typename T, typename Sorter>
    void run_test(Sorter& sorter, std::vector<T>& data, const std::string&);

    // Wykonuje pomiary wydajności dla serii danych
    template<typename T, typename Sorter>
    void run_benchmark(Sorter& sorter, ArrayType array_type, const std::string& algorithm);

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