# edu-pico-c

## Prepare

```bash
cd ~
cd ws
git clone -b master https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init
export PICO_SDK_PATH=~/ws/pico-sdk
```


### Mac

```bash
brew install picotool
brew tap ArmMbed/homebrew-formulae
brew install arm-none-eabi-gcc
```

### Linux

```bash
sudo apt update
sudo apt install gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential
```

### Windows

```bash
```



## Instructions

```bash
cd ..
cd myproject
```

## CMakeLists.txt (project config)

```bash
export PICO_SDK_PATH=~/ws/pico-sdk
cat > CMakeLists.txt << EOF
cmake_minimum_required(VERSION 3.16)
include(\$ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)  # Import Pico SDK

project(pico-blink LANGUAGES C CXX)
pico_sdk_init()  # Initialize Pico SDK

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \${CMAKE_SOURCE_DIR}/bin)

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

