#pragma once
#include <iostream>
using namespace std;

template <typename T, typename Compare>
bool isSorted(const T* arr, size_t size, Compare comp) {
    for(size_t i=0; i<size-1; ++i) {
        if(!comp(arr[i], arr[i+1])) return false;
    }
    return true;
}
template <typename T>
void printArray(const T* arr, int size);

template <typename T>
void loadFromFile(const std::string& filename, T*& arr, int& size);