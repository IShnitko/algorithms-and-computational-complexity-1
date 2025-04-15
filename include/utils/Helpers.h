#pragma once
#include <memory>
#include <vector>
#include <string>
#include <algorithms/SortAlgorithm.h>

#include "config/ConfigParser.h"

namespace Helpers {
    // Szablonowe funkcje pomocnicze:

    // Uruchamia standardowe testy wydajnościowe dla algorytmu
    template<typename T, typename Sorter>
    void run_mode_default(Sorter& sorter, ArrayType array_type, const std::string& algorithm);

    // Testuje algorytm na danych wczytanych z pliku
    template<typename T, typename Sorter>
    void run_test_file(Sorter& sorter, std::vector<T>& data, const std::string& algorithm);

    // Nowe metody:

    // Generuje nowe dane, zapisuje do pliku i testuje algorytm
    template<typename T, typename Sorter>
    void run_test_new_save(
        Sorter& sorter,
        size_t size,
        ArrayType array_type,
        const std::string& algorithm,
        const std::string& filename
    );

    // Generuje nowe dane bez zapisu i testuje algorytm
    template<typename T, typename Sorter>
    void run_test_new_nosave(
        Sorter& sorter,
        size_t size,
        ArrayType array_type,
        const std::string& algorithm
    );

    template<typename T>
    void run_comparative_benchmark(
        const std::vector<std::unique_ptr<SortAlgorithm<T>>>& algorithms,
        ArrayType array_type,
        size_t data_size,
        int runs = 100
    );

    // Zapisuje tablicę do pliku w formacie: rozmiar + elementy w nowych liniach
    template<typename T>
    void saveToFile(const std::vector<T>& data, const std::string& filename);

    // Wyświetla elementy tablicy z ograniczeniem do pierwszych 20 elementów
    template<typename T>
    void printArray(const std::vector<T>& data);

    // Sprawdza czy tablica jest posortowana niemalejąco
    template<typename T>
    bool isSorted(const std::vector<T>& data);

    // Konwertuje typ tablicy na czytelny string
    std::string arrayTypeToString(ArrayType type);

    // Konwertuje typ danych na czytelny string
    std::string dataTypeToString(DataType type);
}
