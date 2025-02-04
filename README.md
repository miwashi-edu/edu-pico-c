# edu-pico-c

[cmake](https://cmake.org/)  
[coreutils](https://www.gnu.org/software/coreutils/)
[isocpp](https://isocpp.org/std/the-standard)  
[cppreference](https://en.cppreference.com/w)  
[cplusplus](https://cplusplus.com/reference/)  
[cout](https://cplusplus.com/reference/iostream/cout/?kw=cout)  

## prepare

### Mac

```bash
brew update
brew install cmake
brew install coreutils # Installs nproc
brew install gcc
```

### Windows

```bash
choco install cmake
```

### Linux

```bash
sudo apt update
sudo apt install cmake
sudo apt install g++
```

## Instructions

```bash
cd ~
cd ws
mkdir myproject && cd myproject
mkdir -p ./{src,include,lib,tests,build}
```

## Set up git

```bash
cat > .gitignore << EOF
/build/
/CMakeCache.txt
/CMakeFiles/
/cmake_install.cmake
/Makefile
/cmake-build-debug
.idea
EOF
git init
git add .
git commit -m "Initial Commit"
```

## CMakeLists.txt (Project Structure)

```bash
cat > CMakeLists.txt << EOF
cmake_minimum_required(VERSION 3.16)
project(myproject LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
EOF
```

## src/CMakeLists.txt (Executable)

```bash
cat > ./src/CMakeLists.txt << EOF
add_executable(hello main.cpp)
EOF
```

## src/main.cpp

```bash
cat > ./src/main.cpp << EOF
#include <iostream>
using namespace std;

int main() {
    cout << "Hello, World!\n";
    return 0;
}
EOF
```

## Build the project

```bash
cmake -B build
make -C build
./bin/hello
```
