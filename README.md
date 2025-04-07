# edu-pico-c

> Hello World with cmake

## Premises

## Login

```
ssh dev@localhost -p 2222
# ctrl-d to end session
```

## Instructions

### Create project (if you didn't create one on level-2)

```
cd ~
cd ws
mkdir -p pico-firmware
cd pico-firmware
git init
```

### scaffold project

```bash
cd ~
cd ws
cd pico-firmware
mkdir src
mkdir include
mkdir tests
mkdir lib
mkdir build
touch CMakeLists.txt
touch ./src/CMakeLists.txt
touch ./src/main.cpp
```

### Optional - Connect to empty repository on git

```bash
git init
git remote add origin git@github.com:<your-username>/<your repository on git>
git checkout -b main
git add .
git commit -m "Initial commit"
git push -u origin main
```

### CMakeLists.txt (Project Structure) !heredoc

> OBS if you write the code, remove the backslas from \${CMAKE_SOURCE_DIR}/bin)

```bash
cat > CMakeLists.txt << EOF
cmake_minimum_required(VERSION 3.16)
project(myproject LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

install(TARGETS hello DESTINATION bin)
EOF
```

### src/CMakeLists.txt (Executable) !heredoc

```bash
cat > ./src/CMakeLists.txt << EOF
add_executable(hello main.cpp)
EOF
```

### src/main.cpp !heredoc

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

### Build the project

```bash
cmake -B build
make -C build
./bin/hello
```

### Reset to commit or delete myproject

#### Delete project
```bash
cd ~
cd ws
rm -rf myproject
```

#### Reset to commit
```bash
cd ~
cd ws
cd myproject
git reset --hard
git clean -df
```
