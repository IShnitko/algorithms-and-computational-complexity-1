#pragma once
#include <algorithm>
#include <cstddef>

namespace QuickSort {
    template <typename T, typename Compare = std::less<T>>
    void sort(T* arr, size_t size, Compare comp = Compare{}) {
        if (size <= 1) return;
        T pivot = arr[size / 2];
        size_t i = 0, j = size - 1;

        while (i <= j) {
            while (comp(arr[i], pivot)) ++i;
            while (comp(pivot, arr[j])) --j;
            if (i <= j) std::swap(arr[i++], arr[j--]);
        }

        if (j > 0) sort(arr, j + 1, comp);
        if (i < size) sort(arr + i, size - i, comp);
    }
}