# edu-pico-c

[cmake](https://cmake.org/)  
[coreutils](https://www.gnu.org/software/coreutils/)

## prepare

### Mac

```bash
brew update
brew install cmake
brew install coreutils # Installs npro
```

### Windows

### Linux

```bash
sudo apt update
sudo apt install cmake
```

## Instructions

```bash
cd ~
cd ws
mkdir myproject && cd myproject
mkdir -p ./{src,include,lib,tests,build}
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
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

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

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
EOF
```

## .gitignore

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
```

## Build the project

```bash
cmake -B build
make -C build
``
