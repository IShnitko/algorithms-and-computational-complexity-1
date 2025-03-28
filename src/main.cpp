#include <iostream>
#include <vector>
#include <fstream>

#include "../include/data_generation/DataGenerator.h"
#include "../include/algorithms/QuickSort.h"
#include "../include/data_types/Person.h"
#include "../include/utils/Helpers.h"
#include "../include/utils/Timer.h"

// Основная логика программы
int main() {
    // Конфигурация тестов
    const int testSizes[] = {10000, 20000, 50000}; // Для демонстрации
    const ArrayType cases[] = {
        ArrayType::Random,
        ArrayType::Sorted,
        ArrayType::ReverseSorted
    };

    // ================== ТЕСТИРОВАНИЕ НА ОБЪЕКТАХ ==================
    std::cout << "\n=== OBJECT SORTING BENCHMARK ===\n";

    for (int size : testSizes) {
        std::cout << "\n[Testing size: " << size << "]\n";

        for (auto arrayType : cases) {
            // 1. Генерация данных
            auto people = generatePeople(size, arrayType);

            // 2. Настройка компаратора
            auto ageComparator = [](const Person& a, const Person& b) {
                return a.age < b.age;
            };

            // 3. Замер времени
            double totalTime = 0.0;
            const int runs = 5;
            bool isValidationPassed = true;

            for (int i = 0; i < runs; ++i) {
                auto peopleCopy = people; // Создание копии

                totalTime += Timer::measureTime([&]() {
                    QuickSort::sort(peopleCopy.data(), peopleCopy.size(), ageComparator);
                });

                // Проверка корректности только на первой итерации
                if (i == 0) {
                    isValidationPassed = isSorted(
                        peopleCopy.data(),
                        peopleCopy.size(),
                        ageComparator
                    );
                }
            }

            // 4. Вывод результатов
            std::cout << "| " << arrayTypeToString(arrayType)
                      << " | Avg time: " << totalTime/runs << " ms"
                      << " | Valid: " << (isValidationPassed ? "YES" : "NO")
                      << " |\n";
        }
    }

    // ================ ДЕМОНСТРАЦИЯ НА МАЛЕНЬКИХ ДАННЫХ ================
    {
        const int demoSize = 5;
        auto demoPeople = generatePeople(demoSize, ArrayType::Random);

        std::cout << "\n=== DEMONSTRATION ===\nBefore sorting:\n";
        for (const auto& p : demoPeople) {
            std::cout << p << "\n";
        }

        QuickSort::sort(demoPeople.data(), demoSize,
            [](auto& a, auto& b) { return a.name < b.name; });

        std::cout << "\nAfter sorting by name:\n";
        for (const auto& p : demoPeople) {
            std::cout << p << "\n";
        }
    }

    return 0;
}