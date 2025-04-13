#pragma once
#include "SortAlgorithm.h"

template<typename T>
class HeapSort : public SortAlgorithm<T> {
    // Naprawia kopiec (max-heap)
    void heapify(std::vector<T> &data, int n, int i) {
        int largest = i;       // Korzeń
        int left = 2 * i + 1;  // Lewe dziecko
        int right = 2 * i + 2; // Prawe dziecko

        // Znajdź największy element między korzeniem a dziećmi
        if (left < n && data[left] > data[largest]) largest = left;
        if (right < n && data[right] > data[largest]) largest = right;

        // Zamień i kontynuuj naprawianie jeśli potrzebne
        if (largest != i) {
            std::swap(data[i], data[largest]);
            heapify(data, n, largest);
        }
    }

public:
    void sort(std::vector<T> &data) override {
        int n = data.size();

        // Buduj kopiec od końca
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(data, n, i);

        // Ekstrakcja elementów z kopca
        for (int i = n - 1; i > 0; i--) {
            std::swap(data[0], data[i]);  // Przenieś korzeń na koniec
            heapify(data, i, 0);          // Napraw zmniejszony kopiec
        }
    }
};
