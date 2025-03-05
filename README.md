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
mkdir myproject
cd myproject
mkdir src
mkdir include
mkdir tests
mkdir lib
mkdir build
touch CMakeLists.txt
touch ./src/CMakeLists.txt
touch ./src/main.cpp
```

## Set up git !heredoc

```bash
cat > .gitignore << EOF
/build/
/CMakeCache.txt
/CMakeFiles/
/cmake_install.cmake
/Makefile
/cmake-build-debug
.idea/
EOF
git init
git add .
git commit -m "Initial Commit"
```

## CMakeLists.txt (Project Structure) !heredoc

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

## src/CMakeLists.txt (Executable) !heredoc

```bash
cat > ./src/CMakeLists.txt << EOF
add_executable(hello main.cpp)
EOF
```

## src/main.cpp !heredoc

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

## Router config file

> Change ssid, psk and key_mgmt

```bash
cat <<EOF > /boot/wpa_supplicant.conf
country=US
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1

network={
    ssid="router"
    psk="your_wifi_password"
    key_mgmt=WPA-PSK
}
EOF
```
