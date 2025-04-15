#pragma once
#include "SortAlgorithm.h"

template <typename T>
class InsertionSort : public SortAlgorithm<T> {
public:
    void sort(std::vector<T>& data) override {
        // Sortowanie przez wstawianie
        for (size_t i = 1; i < data.size(); ++i) {
            T key = data[i];  // Bieżący element do wstawienia
            int j = i - 1;     // Indeks poprzedniego elementu
            // Przesuwanie elementów większych od key w lewo
            while (j >= 0 && data[j] > key) {
                data[j + 1] = data[j];
                j--;
            }
            data[j + 1] = key;  // Wstawienie key w odpowiednie miejsce
        }
    }
    std::string getName() const override { return "insertion_sort"; }
};
