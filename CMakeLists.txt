cmake_minimum_required(VERSION 3.12)
project(AiZO_project_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3 -march=native")

include_directories(include)

add_executable(AiZO_project_1
        src/main.cpp
        src/config/ConfigParser.cpp
        src/data_generation/DataGenerator.cpp
        src/utils/Helpers.cpp
        src/utils/Timer.cpp
)