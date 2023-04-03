#!/bin/bash

# Create a build directory and move into it
BUILD_DIR="build"
[ ! -d $BUILD_DIR ] && mkdir $BUILD_DIR
cd $BUILD_DIR

# Generate the Makefile using CMake
cmake ..

# Build the library
make all

# Install the library system-wide
sudo make install
