#pragma once
#include "SortAlgorithm.h"

template <typename T>
class InsertionSort : public SortAlgorithm<T> {
public:
    void sort(std::vector<T>& data) override {
        for (size_t i = 1; i < data.size(); ++i) {
            T key = data[i];
            int j = i - 1;
            while (j >= 0 && data[j] > key) {
                data[j + 1] = data[j];
                j--;
            }
            data[j + 1] = key;
        }
    }
};