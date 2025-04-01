cmake_minimum_required(VERSION 3.12)
project(AiZO_project_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключение заголовков
include_directories(include)

# Исходные файлы (явное указание пути к src/)
add_executable(AiZO_project_1
        src/main.cpp
        src/config/ConfigParser.cpp
        src/data_generation/DataGenerator.cpp
        src/utils/Helpers.cpp
        src/utils/Timer.cpp
)