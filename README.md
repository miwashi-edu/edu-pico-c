# edu-pico-c

```bash
cd ~
cd ws
mkdir mycppproject && cd mycppproject
mkdir -p ./{src,include,lib,tests,build}
```

## CMakeLists.txt

```bash
cat > CMakeLists.txt << EOF
cmake_minimum_required(VERSION 3.16)
project($PROJECT_NAME LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
EOF
```

## src/CMakeLists.txt

```bash
cat > ./src/CMakeLists.txt << EOF
add_executable(main.cpp)
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
EOF

```

## build.sh

```bash
cat > build.sh << EOF
#!/bin/bash
mkdir -p build
cd build
cmake ..
make -j\$(nproc)
EOF
chmod +x build.sh
```
