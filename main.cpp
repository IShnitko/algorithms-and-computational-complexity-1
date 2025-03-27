#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <string>
#include <stdexcept>

// Шаблонные функции сортировки (заглушки)
template <typename T>
void insertionSort(T* arr, int size) {
    // TODO: Реализация сортировки вставками
}

template <typename T>
void mergeSort(T* arr, int size) {
    // TODO: Реализация сортировки слиянием
}

template <typename T>
void bubbleSort(T* arr, int size) {
    // TODO: Реализация сортировки пузырьком
}

// Вспомогательные функции
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

// Генерация данных
enum class ArrayType { Random, Sorted, ReverseSorted, PartiallySorted };

template <typename T>
void generateArray(T* arr, int size, ArrayType type) {
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
            std::sort(arr, arr + size/3);
            std::sort(arr + 2*size/3, arr + size);
            break;
        default:
            break;
    }
}

// Измерение времени
template <typename T, typename Func>
double measureTime(Func sortFunc, T* arr, int size) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(arr, size);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

// Работа с файлами
template <typename T>
void loadFromFile(const std::string& filename, T*& arr, int& size) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("File not found");

    file >> size;
    arr = new T[size];
    for (int i = 0; i < size; i++) {
        if (!(file >> arr[i])) throw std::runtime_error("Invalid data format");
    }
}

// Основная логика программы
int main() {
    // Конфигурация
    const int testSizes[] = {10000, 20000, 50000, 100000, 200000, 500000, 1000000};
    const ArrayType cases[] = {ArrayType::Random, ArrayType::Sorted,
                              ArrayType::ReverseSorted, ArrayType::PartiallySorted};

    // Тестирование на маленьких данных
    int smallSize = 10;
    int* testArr = new int[smallSize];
    generateArray(testArr, smallSize, ArrayType::Random);

    std::cout << "Before sorting: ";
    printArray(testArr, smallSize);

    insertionSort(testArr, smallSize);

    std::cout << "After sorting: ";
    printArray(testArr, smallSize);

    delete[] testArr;

    // Основные измерения
    for (int size : testSizes) {
        int* arr = new int[size];

        for (auto arrayType : cases) {
            generateArray(arr, size, arrayType);

            // Создаем копию для каждого алгоритма
            int* arrCopy = new int[size];
            std::copy(arr, arr + size, arrCopy);

            double totalTime = 0;
            const int runs = 100;

            for (int i = 0; i < runs; i++) {
                totalTime += measureTime(insertionSort<int>, arrCopy, size);
                // Перегенерируем данные для каждого запуска
                generateArray(arr, size, arrayType);
                std::copy(arr, arr + size, arrCopy);
            }

            std::cout << "Size: " << size
                      << " Type: " << static_cast<int>(arrayType)
                      << " Avg time: " << totalTime/runs << " ms\n";

            delete[] arrCopy;
        }

        delete[] arr;
    }

    return 0;
}
