cmake_minimum_required(VERSION 3.10)
project(AiZO_project_1)

# Настройки компиляции
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключение заголовков
include_directories(include)

# Основные библиотеки
add_subdirectory(src)
add_subdirectory(tests) # Если нужны тесты

## Исполняемый файл
#add_executable(AiZO_project_1 src/main.cpp)
#target_link_libraries(main_app
#        PRIVATE
#        algorithms_lib
#        data_generation_lib
#)