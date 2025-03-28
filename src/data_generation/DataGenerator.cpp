#include "../../include/data_generation/DataGenerator.h"
#include <random>
#include <algorithm>

template<typename T>
void generateArray(T *arr, int size, ArrayType type) {
    std::random_device rd;
    std::mt19937 gen(rd());

    if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> dist(1, 1000);
        for (int i = 0; i < size; i++) arr[i] = dist(gen);
    } else {
        std::uniform_real_distribution<T> dist(0.0, 1.0);
        for (int i = 0; i < size; i++) arr[i] = dist(gen);
    }

    switch (type) {
        case ArrayType::Sorted:
            std::sort(arr, arr + size);
            break;
        case ArrayType::ReverseSorted:
            std::sort(arr, arr + size, std::greater<T>());
            break;
        case ArrayType::PartiallySorted:
            std::sort(arr, arr + size / 3);
            std::sort(arr + 2 * size / 3, arr + size);
            break;
        default:
            break;
    }
}

// Явные инстанциации для поддержки типов
template void generateArray<int>(int*, int, ArrayType);
template void generateArray<double>(double*, int, ArrayType);
template void generateArray<float>(float*, int, ArrayType);

std::string arrayTypeToString(ArrayType type) {
    switch (type) {
        case ArrayType::Random: return "Random";
        case ArrayType::Sorted: return "Sorted";
        case ArrayType::ReverseSorted: return "ReverseSorted";
        case ArrayType::PartiallySorted: return "PartiallySorted";
        default: return "Unknown";
    }
}

std::vector<Person> generatePeople(int count, ArrayType type) {
    std::vector<Person> people;
    static std::string names[] = {"Alice", "Bob", "Charlie", "Diana"};
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> ageDist(18, 65);
    std::uniform_real_distribution<double> salaryDist(1000.0, 10000.0);

    for (int i = 0; i < count; ++i) {
        people.emplace_back(
            names[rng() % 4],
            ageDist(rng),
            salaryDist(rng)
        );
    }

    // Сортировка при необходимости
    switch(type) {
        case ArrayType::Sorted:
            std::sort(people.begin(), people.end(),
                [](auto& a, auto& b) { return a.age < b.age; });
        break;
        case ArrayType::ReverseSorted:
            std::sort(people.rbegin(), people.rend(),
                [](auto& a, auto& b) { return a.age < b.age; });
        break;
        case ArrayType::PartiallySorted:
            std::sort(people.begin(), people.begin() + people.size()/3,
                [](auto& a, auto& b) { return a.age < b.age; });
        std::sort(people.end() - people.size()/3, people.end(),
            [](auto& a, auto& b) { return a.age < b.age; });
        break;
        default: break;
    }

    return people;
}
