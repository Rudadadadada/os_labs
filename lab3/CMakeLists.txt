add_executable(lab3
        main.cpp
        src/average.cpp include/average.hpp
        src/utils.cpp include/utils.hpp)

target_include_directories(lab3 PRIVATE include)