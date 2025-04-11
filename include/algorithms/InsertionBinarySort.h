#pragma once
#include <vector>
#include "SortAlgorithm.h"

template <typename T>
class BinaryInsertionSort : public SortAlgorithm<T> {
private:
    // Бинарный поиск позиции для вставки (не изменяет данные)
    int findPosition(const std::vector<T>& data, const T& key, int low, int high) {
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (data[mid] < key) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return low; // Возвращает индекс для вставки
    }

public:
    void sort(std::vector<T>& data) override {
        for (size_t i = 1; i < data.size(); ++i) {
            T key = data[i];
            
            // Находим позицию через бинарный поиск
            int pos = findPosition(data, key, 0, i - 1);
            
            // Сдвигаем элементы и вставляем key
            for (int j = i - 1; j >= pos; --j) {
                data[j + 1] = data[j];
            }
            data[pos] = key;
        }
    }
};
