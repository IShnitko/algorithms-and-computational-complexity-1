cmake_minimum_required(VERSION 3.10)
project(SortingAlgorithms)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(main_app
        src/main.cpp
        src/algorithms/QuickSort.cpp
        src/algorithms/HeapSort.cpp
        src/data_generation/DataGenerator.cpp
        src/data_types/Person.cpp
        src/utils/Helpers.cpp
        src/utils/Timer.cpp
)