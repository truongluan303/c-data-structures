# Create a build directory and move into it
mkdir build
cd build

# Generate the Makefile using CMake
cmake ..

# Build the library
make all

# Install the library system-wide
sudo make install
sudo ldconfig
