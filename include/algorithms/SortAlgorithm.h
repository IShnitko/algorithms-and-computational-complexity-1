#pragma once
#include <vector>

// Abstrakcyjna klasa bazowa dla algorytmów sortowania
template <typename T>
class SortAlgorithm {
public:
    // Wirtualna metoda sortująca (do implementacji w klasach pochodnych)
    virtual void sort(std::vector<T>& data) = 0;

    // Wirtualny destruktor (domyślna implementacja)
    virtual ~SortAlgorithm() = default;
};