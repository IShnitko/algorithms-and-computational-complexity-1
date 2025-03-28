#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <random>
#include <string>
#include <stdexcept>
#include <algorithm>

#include "../include/algorithms/QuickSort.h"
#include "../include/data_types/Person.h"

// Шаблонные функции сортировки (заглушки)
template<typename T>
void insertionSort(T *arr, int size) {
    // TODO: Реализация сортировки вставками
}

#include <iostream>
using namespace std;

// Восстановление свойства max-heap в поддереве с корнем i
template <typename T>
void heapify(T* arr, int size, int i) {
    int largest = i;        // Инициализируем наибольший элемент как корень
    int left = 2 * i + 1;  // Левый потомок
    int right = 2 * i + 2; // Правый потомок

    // Если левый потомок больше корня
    if (left < size && arr[left] > arr[largest])
        largest = left;

    // Если правый потомок больше текущего наибольшего
    if (right < size && arr[right] > arr[largest])
        largest = right;

    // Если наибольший элемент не корень
    if (largest != i) {
        swap(arr[i], arr[largest]);
        // Рекурсивно восстанавливаем поддерево
        heapify(arr, size, largest);
    }
}

// Построение max-heap из массива
template <typename T>
void buildMaxHeap(T* arr, int size) {
    // Начинаем с последнего нелистового узла
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);
}

// Сортировка кучей
template <typename T>
void heapSort(T* arr, int size) {
    // Построение max-heap
    buildMaxHeap(arr, size);

    // Последовательно извлекаем элементы из кучи
    for (int i = size - 1; i > 0; i--) {
        // Перемещаем текущий корень в конец
        swap(arr[0], arr[i]);
        // Вызываем heapify на уменьшенной куче
        heapify(arr, i, 0);
    }
}

template <typename T, typename Compare>
void quickSort(std::vector<T>& arr, int low, int high, Compare comp) {
    if (low < high) {
        T pivot = arr[(low + high) / 2];
        int i = low, j = high;

        while (i <= j) {
            while (comp(arr[i], pivot)) i++;
            while (comp(pivot, arr[j])) j--;
            if (i <= j) {
                std::swap(arr[i], arr[j]);
                i++;
                j--;
            }
        }

        if (low < j) quickSort(arr, low, j, comp);
        if (i < high) quickSort(arr, i, high, comp);
    }
}

template<typename T>
void shellSort(T *arr, int size) {
    // TODO: Реализация сортировки shell (читать инструкцию)
}

template<typename T> // Убрать. Было создано для теста
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

class Person { // structure for quickSort on objects
public:
    std::string name;
    int age;
    double salary;

    Person(std::string n, int a, double s)
        : name(std::move(n)), age(a), salary(s) {}

    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << p.name << " (" << p.age << ", " << p.salary << ")";
        return os;
    }
};

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

// Основная логика программы
int main() { // TODO: remake new main file according to new project structure
    // Конфигурация
    const int testSizes[] = {10000, 20000, 50000, 100000, 200000, 500000, 1000000};
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

    quickSort(testArr, smallSize);

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
                totalTime += measureTime(quickSort<int>, arrCopy, size);
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
