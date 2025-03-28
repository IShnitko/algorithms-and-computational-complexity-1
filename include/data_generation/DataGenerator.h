#pragma once
#include "ArrayType.h"
#include "../data_types/Person.h"
#include <vector>

template <typename T>
void generateArray(T* arr, int size, ArrayType type);
extern template void generateArray<int>(int*, int, ArrayType);
extern template void generateArray<double>(double*, int, ArrayType);
extern template void generateArray<float>(float*, int, ArrayType);

std::vector<Person> generatePeople(int count, ArrayType type);
std::string arrayTypeToString(ArrayType type);