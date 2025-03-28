#pragma once
#include "ArrayType.h"
#include "../config/ConfigParser.h"
#include "../data_types/Person.h"
#include <vector>

template <typename T>
void generateArray(T* arr, int size, Config::ArrayType type);

// Явные объявления инстанциаций
extern template void generateArray<int>(int*, int, Config::ArrayType);
extern template void generateArray<double>(double*, int, Config::ArrayType);
extern template void generateArray<char>(char*, int, Config::ArrayType);

std::vector<Person> generatePeople(int size, Config::ArrayType type);
std::string arrayTypeToString(ArrayType type);