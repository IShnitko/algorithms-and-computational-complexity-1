#pragma once
#include "ArrayType.h"
#include "../data_types/Person.h"
#include <vector>

template <typename T>
void generateArray(T* arr, int size, ArrayType type);

std::vector<Person> generatePeople(int count, ArrayType type);
std::string arrayTypeToString(ArrayType type);