# edu-pico-c

> Hello World with cmake

## Premises

## Login

```
ssh dev@localhost -p 2222
# ctrl-d to end session
```

## Instructions

### Create project

```
cd ~
cd ws
mkdir -p myproject
cd myproject
gh repo create
```

### scaffold project

```bash
mkdir src
mkdir include
mkdir tests
mkdir lib
mkdir build
touch CMakeLists.txt
touch ./src/CMakeLists.txt
touch ./src/main.cpp
```

### Set up git

> We use git to
> 1. Share our work on github
> 2. Repeat when memorising
>
> The *.ignore* **url** is not difficult to memorise, it is very useful if you need python .gitignore just change *C%2B%2B* (C++) to *python*.

```bash
curl -o .gitignore https://raw.githubusercontent.com/github/gitignore/main/C%2B%2B.gitignore
git init
git branch -m main # if you didn't change git to use main instead of maste
git add .
git commit -m "Initial Commit"
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
