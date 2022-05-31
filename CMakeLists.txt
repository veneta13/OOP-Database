cmake_minimum_required(VERSION 3.0.0)
project(stack VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(tests
        tests/test.cpp
        source/value.cpp
        source/integer_value.cpp)

add_executable(main
        source/main.cpp
        source/value.cpp
        source/integer_value.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
