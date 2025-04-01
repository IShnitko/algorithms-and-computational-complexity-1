#pragma once
#include <vector>

template <typename T>
class SortAlgorithm {
public:
    virtual void sort(std::vector<T>& data) = 0;
    virtual ~SortAlgorithm() = default;
};