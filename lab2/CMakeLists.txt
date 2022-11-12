add_executable(lab2
        main.cpp
        src/parent.cpp include/parent.hpp
        src/utils.cpp include/utils.hpp)

target_include_directories(lab2 PRIVATE include)

add_executable(child
        src/child.cpp
        src/utils.cpp include/utils.hpp)

target_include_directories(child PRIVATE include)

add_dependencies(lab2 child)