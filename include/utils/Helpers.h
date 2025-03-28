#pragma once
#include <iostream>
using namespace std;

template <typename T>
bool isSorted(const T* arr, int size);

template <typename T>
void printArray(const T* arr, int size);

template <typename T>
void loadFromFile(const std::string& filename, T*& arr, int& size);