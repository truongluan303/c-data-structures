# C Data Structures Library
An implementation of popular data structures in C programming language.

## Build & Install The Shared Library
Run the `build.sh` script to automatically build and install the library.

If the script fails, manually perform the following commands:

Create a directory for building the project
```bash
mkdir build && cd build
```
Generate the Makefile using CMake
```bash
cmake ..
```
Build the library
```bash
make all
```
Install the library system-wide
```bash
sudo make install
```
