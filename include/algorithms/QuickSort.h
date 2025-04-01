#pragma once
#include "SortAlgorithm.h"

template<typename T>
class QuickSort : public SortAlgorithm<T> {
    int partition(std::vector<T> &data, int low, int high) {
        int pivotIndex = low + (high - low)/2;
        std::swap(data[pivotIndex], data[high]);
        T pivot = data[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++) {
            if (data[j] < pivot) {
                i++;
                std::swap(data[i], data[j]);
            }
        }
        std::swap(data[i + 1], data[high]);
        return i + 1;
    }

    void quickSort(std::vector<T> &data, int low, int high) {
        if (low < high) {
            int pi = partition(data, low, high);
            quickSort(data, low, pi - 1);
            quickSort(data, pi + 1, high);
        }
    }

public:
    void sort(std::vector<T> &data) override {
        quickSort(data, 0, data.size() - 1);
    }
};
