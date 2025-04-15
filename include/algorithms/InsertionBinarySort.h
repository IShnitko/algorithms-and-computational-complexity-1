#pragma once
#include <vector>
#include "SortAlgorithm.h"

template <typename T>
class BinaryInsertionSort : public SortAlgorithm<T> {
private:
    // Binarnie znajduje pozycję do wstawienia elementu
    int findPosition(const std::vector<T>& data, const T& key, int low, int high) {
        while (low <= high) {
            int mid = low + (high - low) / 2;  // Środkowy indeks
            if (data[mid] < key) {
                low = mid + 1;  // Szukaj w prawej połowie
            } else {
                high = mid - 1; // Szukaj w lewej połowie
            }
        }
        return low;  // Zwraca indeks do wstawienia
    }

public:
    void sort(std::vector<T>& data) override {
        for (size_t i = 1; i < data.size(); ++i) {
            T key = data[i];  // Bieżący element

            // Znajdź pozycję przy użyciu wyszukiwania binarnego
            int pos = findPosition(data, key, 0, i - 1);

            // Przesuń elementy i wstaw key
            for (int j = i - 1; j >= pos; --j) {
                data[j + 1] = data[j];
            }
            data[pos] = key;
        }
    }
    std::string getName() const override { return "insertion_binary_sort"; }
};
