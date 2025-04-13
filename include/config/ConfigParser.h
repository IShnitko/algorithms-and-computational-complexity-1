#pragma once
#include <string>
#include "data_generation/ArrayType.h"

// Typy danych obsługiwane przez program
enum class DataType {
    INT,    // Liczby całkowite (np. 1, 2, 3)
    FLOAT,  // Liczby zmiennoprzecinkowe pojedynczej precyzji (np. 3.14f)
    CHAR,   // Pojedyncze znaki (np. 'a', 'Z')
    DOUBLE  // Liczby zmiennoprzecinkowe podwójnej precyzji (np. 3.141592)
};
enum class Mode {
    DEFAULT,
    TEST_FILE,
    TEST_NEW_SAVE,
    TEST_NEW_NOSAVE
};
// Konfiguracja programu wczytana z pliku
struct Config {
    Mode mode;
    int size;
    std::string algorithm;   // Nazwa algorytmu sortowania (np. "quick_sort")
    DataType data_type;      // Typ generowanych/przetwarzanych danych
    ArrayType array_type;    // Typ tablicy (np. losowa, posortowana)
    std::string input_file;  // Ścieżka do pliku z danymi (opcjonalnie)
};

// Klasa do parsowania pliku konfiguracyjnego
class ConfigParser {
public:
    // Metoda wczytująca konfigurację z pliku
    static Config parse(const std::string &filename);
};
