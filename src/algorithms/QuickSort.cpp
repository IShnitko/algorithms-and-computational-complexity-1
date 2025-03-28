#include "../../include/algorithms/QuickSort.h"
#include "../../include/data_types/Person.h"
#include <algorithm>

template <typename T, typename Compare>
void quickSort(T* arr, int low, int high, Compare comp) {
    if (low < high) {
        T pivot = arr[(low + high) / 2];
        int i = low, j = high;
        
        while (i <= j) {
            while (comp(arr[i], pivot)) i++;
            while (comp(pivot, arr[j])) j--;
            if (i <= j) {
                std::swap(arr[i], arr[j]);
                i++;
                j--;
            }
        }
        
        if (low < j) quickSort(arr, low, j, comp);
        if (i < high) quickSort(arr, i, high, comp);
    }
}

// Явные инстанциации для нужных типов
template void quickSort<int>(int*, int, int, std::less<int>);
template void quickSort<Person>(Person*, int, int, std::function<bool(const Person&, const Person&)>);
