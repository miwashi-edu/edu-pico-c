# edu-pico-c

```bash
```



## Instructions

```bash
ssh dev@localhost -p 2222
cd ~
cd ws
cd pico-firmware
```

## CMakeLists.txt (project config)

> Note: if you type this, don't write the backslash in "\${CMAKE_SOURCE_DIR}/bin"

```bash
cat > CMakeLists.txt << EOF
cmake_minimum_required(VERSION 3.16)
project(pico-blink LANGUAGES C CXX)

# Use the pre-installed Pico SDK (cloned manually)
include(\$ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Initialize the SDK (will auto-select toolchain)
pico_sdk_init()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "\${CMAKE_SOURCE_DIR}/bin")

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

