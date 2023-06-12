# Clone the replxx and Google Test dependencies
git clone https://github.com/AmokHuginnsson/replxx.git ./deps/replxx
git clone https://github.com/google/googletest.git ./deps/googletest

# Create the build directory and navigate into it
New-Item -ItemType Directory -Force -Path ./build
Set-Location -Path ./build

# Run CMake to generate the build system
cmake ..

# Build the project
make
