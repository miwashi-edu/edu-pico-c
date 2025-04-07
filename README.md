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
mkdir blink
touch ./blink/CMakeLists.txt
curl -o ./blink/main.c https://raw.githubusercontent.com/raspberrypi/pico-examples/master/blink/blink.c
```

## CMakeLists.txt (project config)

> Note: if you type this, don't write the backslash in "\${CMAKE_SOURCE_DIR}/bin"

```bash
cat > CMakeLists.txt << EOF
cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)
include(\$ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
#include(pico_extras_import_optional.cmake)

project(pico_firmware C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "2.1.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 2.1.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

if (NOT DEFINED PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS)
    set(PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS 3000)
endif()

pico_sdk_init()

function(add_subdirectory_exclude_platforms NAME)
    if (ARGN)
        if (PICO_PLATFORM IN_LIST ARGN)
            message("Skipping ${NAME} example which is unsupported on this platform")
            return()
        endif()
        foreach(PATTERN IN LISTS ARGN)
            string(REGEX MATCH "\${PATTERN}" MATCHED "${PICO_PLATFORM}")
            string(REGEX MATCH "\${PATTERN}" MATCHED "${PICO_PLATFORM}")
            if (MATCHED)
                message("Skipping \${NAME} example which is unsupported on this platform")
                return()
            endif()
        endforeach()
    endif()
    add_subdirectory(\${NAME})
endfunction()


add_subdirectory_exclude_platforms(blink)
EOF
```

## blink/CMakeLists.txt

```bash
cat > ./blink/CMakeLists.txt << EOF
add_executable(\${PROJECT_NAME} main.c)

target_link_libraries(\${PROJECT_NAME} pico_stdlib)

pico_enable_stdio_usb(\${PROJECT_NAME} 1)
pico_enable_stdio_uart(\${PROJECT_NAME} 0)

pico_add_extra_outputs(\${PROJECT_NAME})
EOF
```

## Build

```bash
cmake -B build
cmake --build build
cp -af ./bin/*.elf ~/share/
cp -af ./bin/*.uf2 ~/share/
```

