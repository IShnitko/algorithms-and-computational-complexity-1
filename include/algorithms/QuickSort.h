#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <functional>

template <typename T, typename Compare>
void quickSort(T* arr, int low, int high, Compare comp);

#endif