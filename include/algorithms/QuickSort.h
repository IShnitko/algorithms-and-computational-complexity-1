#pragma once
#include "SortAlgorithm.h"

template<typename T>
class QuickSort : public SortAlgorithm<T> {
    // Metoda podziału tablicy według pivota
    int partition(std::vector<T> &data, int low, int high) {
        // Wybór pivota (środkowy element) i zamiana z ostatnim elementem
        int pivotIndex = low + (high - low)/2;
        std::swap(data[pivotIndex], data[high]);
        T pivot = data[high];

        int i = low - 1;  // Indeks mniejszy od pivota

        // Przechodzenie przez elementy i zamiana mniejszych od pivota
        for (int j = low; j <= high - 1; j++) {
            if (data[j] < pivot) {
                i++;
                std::swap(data[i], data[j]);
            }
        }

        // Umieszczenie pivota we właściwym miejscu
        std::swap(data[i + 1], data[high]);
        return i + 1;
    }

    // Rekurencyjna implementacja sortowania szybkiego
    void quickSort(std::vector<T> &data, int low, int high) {
        if (low < high) {
            // Podział tablicy i rekurencyjne sortowanie podtablic
            int pi = partition(data, low, high);
            quickSort(data, low, pi - 1);
            quickSort(data, pi + 1, high);
        }
    }

public:
    // Główna metoda sortująca (implementacja z klasy bazowej)
    void sort(std::vector<T> &data) override {
        quickSort(data, 0, data.size() - 1);
    }
    std::string getName() const override { return "quick_sort"; }
};
