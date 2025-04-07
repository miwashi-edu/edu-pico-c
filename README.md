# edu-pico-c

```bash
```



## Instructions

```bash
ssh dev@localhost -p 2222
ecport PICO_SDK_PATH=/opt/pico-sdk # If still missing
echo 'export PICO_SDK_PATH=/opt/pico-sdk' >> /home/dev/.zshrc
cd ~
cd ws
cd pico-firmware
```

## CMakeLists.txt (project config)

> Note: if you type this, don't write the backslash in "\${CMAKE_SOURCE_DIR}/bin"

```bash
cat > CMakeLists.txt << EOF
cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME pico-firmware)
project(\${PROJECT_NAME} LANGUAGES C CXX ASM)

# Load the Pico SDK from the environment
include(\$ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

# Set output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "\${CMAKE_SOURCE_DIR}/bin")

# Add source folder
add_subdirectory(src)
EOF
```

## src/CMakeLists.txt

```bash
cat > ./src/CMakeLists.txt << EOF
add_executable(\${PROJECT_NAME} main.cpp)

target_link_libraries(\${PROJECT_NAME} pico_stdlib)

pico_enable_stdio_usb(\${PROJECT_NAME} 1)
pico_enable_stdio_uart(\${PROJECT_NAME} 0)

pico_add_extra_outputs(\${PROJECT_NAME})
EOF
```
## ./src/main.cpp

```bash
cat > ./src/main.cpp << EOF
#include "pico/stdlib.h"

int main() {
    const uint LED_PIN = 25; // Pico onboard LED (GPIO 25)
    
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(500);
        gpio_put(LED_PIN, 0);
        sleep_ms(500);
    }
}
EOF
```

## Build

```bash
cmake -B build
cmake --build build
cp -af ./bin/*.elf ~/share/
cp -af ./bin/*.uf2 ~/share/
```

