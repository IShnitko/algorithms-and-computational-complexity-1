#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <algorithm> // Для std::swap

namespace QuickSort {

    // Предварительное объявление шаблонной функции
    template <typename T, typename Compare>
    void quickSort(T* arr, int low, int high, Compare comp);

    // Основной публичный интерфейс
    template <typename T, typename Compare>
    void sort(T* arr, int size, Compare comp) {
        quickSort(arr, 0, size - 1, comp);
    }

    // Реализация быстрой сортировки
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

            quickSort(arr, low, j, comp);
            quickSort(arr, i, high, comp);
        }
    }

} // namespace QuickSort

#endif