#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

# Run Conan to install dependencies
conan install . --output-folder=build --build=missing

# Create the build directory if it doesn't exist
mkdir -p build

# Navigate to the build directory
cd build

# Configure the project using CMake
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release


# Build the project
cmake --build .

# Navigate back to the root directory
cd ..

# Run the executable
./build/parseit


