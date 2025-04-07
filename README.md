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
project(pico-firmware LANGUAGES C CXX)
include(\$ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(\${PROJECT} C CXX ASM)
pico_sdk_init()

target_link_libraries(\${PROJECT} pico_stdlib)
pico_add_extra_outputs(\${PROJECT})
pico_enable_stdio_usb(\${PROJECT} 1)
pico_enable_stdio_uart(\${PROJECT} 0)

add_subdirectory(src)
EOF
```

## src/CMakeLists.txt

```bash
cat > ./src/CMakeLists.txt << EOF
add_executable(pico-blink main.cpp)

# Link necessary Pico libraries
target_link_libraries(pico-blink pico_stdlib)

# Enable USB and UART output
pico_enable_stdio_usb(pico-blink 1)
pico_enable_stdio_uart(pico-blink 1)

# Create .uf2 firmware for flashing to the Pico
pico_add_extra_outputs(pico-blink)
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

