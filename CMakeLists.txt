cmake_minimum_required(VERSION 3.0.0)
project(stack VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(tests
        source/dynamic_array.cpp
        tests/test.cpp
        source/value.cpp
        source/integer_value.cpp
        source/float_value.cpp
        source/string_value.cpp
        source/null_value.cpp
        source/integer_column.cpp)

add_executable(main
        source/dynamic_array.cpp
        source/main.cpp
        source/value.cpp
        source/integer_value.cpp
        source/float_value.cpp
        source/string_value.cpp
        source/null_value.cpp
        source/integer_column.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
