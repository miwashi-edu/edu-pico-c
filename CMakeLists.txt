cmake_minimum_required(VERSION 3.13)

# Set project name
project(PicoProject C CXX ASM)

# Include Pico SDK
set(PICO_SDK_PATH ${CMAKE_SOURCE_DIR}/pico-sdk)
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Initialize the SDK
pico_sdk_init()

# Add executable
add_executable(pico_firmware
        src/main.c
        src/wifi_connect.c
        src/update_firmware.c
)

# Link necessary libraries
target_link_libraries(pico_firmware
        pico_stdlib
        pico_cyw43_arch_lwip_threadsafe_background  # Wi-Fi support for Pico W
        hardware_flash  # Access flash memory
)

# Enable USB output
pico_enable_stdio_usb(pico_firmware 1)
pico_enable_stdio_uart(pico_firmware 1)

# Create UF2 file
pico_add_extra_outputs(pico_firmware)
