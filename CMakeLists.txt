cmake_minimum_required(VERSION 3.15)
project(ParseCSV)

# Include Conan-generated files
# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)  
# conan_basic_setup(TARGETS)  

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include directories
include_directories(include)

add_subdirectory(external/Catch2)

# Add the executable and include all relevant source files
add_executable(parseit
  src/main.cpp
  include/Graph.cpp
  include/MovieParser.cpp
  # tests/test_main.cpp
  # tests/test_graph.cpp
)

# Find required packages (Conan should handle this)
find_package(fmt REQUIRED CONFIG)
find_package(rapidcsv REQUIRED CONFIG)
find_package(nlohmann_json REQUIRED CONFIG)

# Link libraries to the executable
target_link_libraries(parseit PRIVATE fmt::fmt rapidcsv::rapidcsv nlohmann_json::nlohmann_json Catch2::Catch2WithMain) 

# Enable testing
enable_testing()
