cmake_minimum_required(VERSION 3.10)

add_executable(main_app
        config/ConfigParser.cpp
        data_types/Person.cpp       # Только НЕ шаблонные реализации
        data_generation/DataGenerator.cpp
        utils/Helpers.cpp
        utils/Timer.cpp
        main.cpp
        # НЕ включаем QuickSort.cpp
)

set_target_properties(main_app PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)