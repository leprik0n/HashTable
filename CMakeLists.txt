cmake_minimum_required(VERSION 2.8)

project(HT CXX)

if (MSVC)
    add_definitions(/W4)
else()
    add_definitions(-Wall)
    add_definitions(-std=c++11)
endif()

include_directories(include)

enable_testing()

add_executable(test_hash main.cpp)

add_test(NAME ${PROJECT_NAME} COMMAND test_hash)
