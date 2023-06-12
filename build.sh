#!/bin/bash

# Clone the replxx repository
echo "Cloning replxx..."
git clone https://github.com/AmokHuginnsson/replxx.git deps/replxx

# Clone the Google Test repository
echo "Cloning Google Test..."
git clone https://github.com/google/googletest.git deps/googletest

echo "All dependencies have been cloned successfully!"

# Create a build directory
mkdir -p build && cd build || exit

# Configure the build with CMake
echo "Configuring the build with CMake..."
cmake ..

# Build the project
echo "Building the project..."
make

echo "The project has been built successfully!"
