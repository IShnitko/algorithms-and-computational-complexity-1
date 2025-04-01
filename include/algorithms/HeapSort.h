#pragma once
#include "SortAlgorithm.h"

template<typename T>
class HeapSort : public SortAlgorithm<T> {
    void heapify(std::vector<T> &data, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && data[left] > data[largest]) largest = left;
        if (right < n && data[right] > data[largest]) largest = right;

        if (largest != i) {
            std::swap(data[i], data[largest]);
            heapify(data, n, largest);
        }
    }

public:
    void sort(std::vector<T> &data) override {
        int n = data.size();
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(data, n, i);

        for (int i = n - 1; i > 0; i--) {
            std::swap(data[0], data[i]);
            heapify(data, i, 0);
        }
    }
};
