#include "../../include/utils/Helpers.h"
#include <fstream>
#include <iostream>

template <typename T>
bool isSorted(const T* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

template <typename T>
void printArray(const T* arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

template<typename T>
void loadFromFile(const std::string &filename, T *&arr, int &size) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("File not found");

    file >> size;
    arr = new T[size];
    for (int i = 0; i < size; i++) {
        if (!(file >> arr[i])) throw std::runtime_error("Invalid data format");
    }
}
// Явные инстанциации
template bool isSorted<int>(const int*, int);
template void printArray<int>(const int*, int);
template void loadFromFile<int>(const std::string&, int*&, int&);