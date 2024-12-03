cmake_minimum_required(VERSION 3.15)
project(ParseCSV)

# Include the Conan-generated toolchain file
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(parseit src/main.cpp)

find_package(fmt REQUIRED CONFIG)
find_package(rapidcsv REQUIRED CONFIG)
find_package(nlohmann_json REQUIRED CONFIG)

target_link_libraries(parseit PRIVATE fmt::fmt rapidcsv::rapidcsv nlohmann_json::nlohmann_json)

