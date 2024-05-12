#!/bin/bash

# Capture the user's current directory
ORIGINAL_DIR=$(pwd)

# Get the directory of the current script
DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Set the compilers to Clang
export CC=clang
export CXX=clang++

# Navigate to the directory of the script
cd "$DIR"
cd ..
# Navigate to the linux_build directory and build each configuration
cd linux_build/debug
cmake --build .
echo

# Return to the original directory
cd "$ORIGINAL_DIR"

echo "Linux debug build completed"

