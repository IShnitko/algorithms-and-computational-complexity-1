#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <string>
#include <stdexcept>
#include <algorithm>

// Шаблонные функции сортировки (заглушки)
template<typename T>
void insertionSort(T *arr, int size) {
    // TODO: Реализация сортировки вставками
}

template<typename T>
void heapSort(T *arr, int size) {
    // TODO: Реализация сортировки через кучу
}


template<typename T>
void quickSort(T *arr, int size) {
    // TODO: Реализация быстрой сортировки в версии с объектами как типы данных, обратить внимание как тип данных влияет на конечную скорость
}

template<typename T>
void shellSort(T *arr, int size) {
    // TODO: Реализация сортировки shell (читать инструкцию)
}

template<typename T> // убрать. Было создано для теста
void bubbleSort(T *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Вспомогательные функции
template<typename T>
bool isSorted(const T *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

template<typename T>
void printArray(const T *arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

// Генерация данных
enum class ArrayType { Random, Sorted, ReverseSorted, PartiallySorted };

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

// Измерение времени
template<typename T, typename Func>
double measureTime(Func sortFunc, T *arr, int size) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(arr, size);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

// Работа с файлами
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

std::string arrayTypeToString(ArrayType type) {
    switch (type) {
        case ArrayType::Random: return "Random";
        case ArrayType::Sorted: return "Sorted";
        case ArrayType::ReverseSorted: return "ReverseSorted";
        case ArrayType::PartiallySorted: return "PartiallySorted";
        default: return "Unknown";
    }
}

// Основная логика программы
int main() {
    // Конфигурация
    // const int testSizes[] = {10000, 20000, 50000, 100000, 200000, 500000, 1000000};
    const int testSizes[] = {100, 200, 500, 1000, 2000, 5000, 10000};
    const ArrayType cases[] = {
        ArrayType::Random, ArrayType::Sorted,
        ArrayType::ReverseSorted, ArrayType::PartiallySorted
    };

    // Тестирование на маленьких данных
    int smallSize = 10;
    int *testArr = new int[smallSize];
    generateArray(testArr, smallSize, ArrayType::Random);

    std::cout << "Before sorting: ";
    printArray(testArr, smallSize);

    bubbleSort(testArr, smallSize);

    std::cout << "After sorting: ";
    printArray(testArr, smallSize);

    delete[] testArr;
    int i = 1;
    // Основные измерения
    for (int size: testSizes) {
        int *arr = new int[size];
        int j = 1;
        for (auto arrayType: cases) {
            generateArray(arr, size, arrayType);

            // Создаем копию для каждого алгоритма
            int *arrCopy = new int[size];
            std::copy(arr, arr + size, arrCopy);

            double totalTime = 0;
            const int runs = 100;

            for (int i = 0; i < runs; i++) {
                totalTime += measureTime(bubbleSort<int>, arrCopy, size);
                // Перегенерируем данные для каждого запуска
                generateArray(arr, size, arrayType);
                std::copy(arr, arr + size, arrCopy);
            }

            std::cout << i << "." << j << " "
                    << "Size: " << size
                    << " Type: " << arrayTypeToString(arrayType)
                    << " Avg time: " << totalTime / runs << " ms\n";

            delete[] arrCopy;
            j++;
        }
        i++;
        delete[] arr;
    }

    return 0;
}
