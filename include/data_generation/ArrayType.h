#pragma once

// Typy generowanych tablic testowych:
enum class ArrayType {
    RANDOM,              // Losowe dane
    SORTED,              // Posortowane rosnąco
    REVERSE_SORTED,      // Posortowane malejąco
    PARTIALLY_SORTED_33, // Częściowo posortowane (33%)
    PARTIALLY_SORTED_66, // Częściowo posortowane (66%)
    ALL                  // Wszystkie typy tablic
};