cmake_minimum_required(VERSION 3.15)
project(ParseCSV)

# Include the Conan-generated toolchain file
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include directories
include_directories(include)

# Add the executable and include all relevant source files
add_executable(parseit src/main.cpp include/Graph.cpp)

# Find required packages
find_package(fmt REQUIRED CONFIG)
find_package(rapidcsv REQUIRED CONFIG)
find_package(nlohmann_json REQUIRED CONFIG)

# Link libraries to the executable
target_link_libraries(parseit PRIVATE fmt::fmt rapidcsv::rapidcsv nlohmann_json::nlohmann_json)

