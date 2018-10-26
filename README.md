# CPP-Project-Template
A program for a simple CMake/Makefile-based C / C++ Epitech project. Let's you choose if you want a C or a C++ project and wether you want a Makefile or a CMakeList.txt.


## Requirements

- CMake
- A compiler that supports C++14 or newer

## Compilation and Installation

```bash
cmake -H. -Bbuild
cmake --build build -- -j3
```

The binary will be located in the `./bin` directory.

## Usage

```bash
./app
```
Then follow the instructions on the screen.

### UNIT TESTS
If you want to use Catch UT, you need to have the catch.hpp file in a catch folder.
```bash
$ ~/Documents/save/catch/catch.hpp
```
