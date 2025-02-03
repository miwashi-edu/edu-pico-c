# edu-pico-c

```bash
cd ~
cd ws
mkdir mycppproject && cd mycppproject
mkdir -p ./{src,include,lib,tests,build}
echo "target_link_libraries(mycppproject PRIVATE my_lib)" >> ./src/CMakeLists.txt
chmod +x ./build.sh

# Print success message
echo "✅ C++ CMake project mycppproject created successfully!"
echo "➡️  Run './build.sh' to build the project."
```

```bash
# Create the main CMakeLists.txt
cat > ./CMakeLists.txt << EOF
cmake_minimum_required(VERSION 3.16)
project(mycppproject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(tests)
enable_testing()
EOF
```

```bash
cat > ./lib/CMakeLists.txt << EOF
add_library(my_lib my_lib.cpp)
target_include_directories(my_lib PUBLIC include)
EOF
```

```bash
cat > ./include/my_lib.h << EOF
#pragma once

#include <string>

std::string my_function();

#endif // MY_LIB_H
EOF

cat > ./lib/my_lib.cpp << EOF
#include "my_lib.h"

std::string my_function() {
return "Hello from my_lib!";
}
EOF
```

```bash
cat > ./tests/CMakeLists.txt << EOF
include(FetchContent)

FetchContent_Declare(
googletest
URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)

FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(tests test_main.cpp)
target_link_libraries(tests PRIVATE my_lib gtest_main)

add_test(NAME MyLibraryTests COMMAND tests)
EOF
```

```bash
# Create test file
cat > ./tests/test_main.cpp << EOF
#include "gtest/gtest.h"
#include "my_lib.h"

TEST(MyLibTest, TestFunction) {
EXPECT_EQ(my_function(), "Hello from my_lib!");
}

int main(int argc, char **argv) {
::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}
EOF
```

```bash
cat > .gitignore << EOF
/build/
/CMakeCache.txt
/CMakeFiles/
/cmake_install.cmake
/Makefile
EOF
```

```bash
cat > ./src/CMakeLists.txt << EOF
add_executable(mycppproject} main.cpp)
target_include_directories(mycppproject PRIVATE ./src/include)
target_link_libraries(mycppproject PRIVATE my_lib)  # 🔥 Added this!
EOF

# Create main.cpp
cat > ./src/main.cpp << EOF
#include <iostream>
#include "my_lib.h"

int main() {
std::cout << "Hello from mycppproject!" << std::endl;
std::cout << "Library says: " << my_function() << std::endl;
return 0;
}
EOF
```

```bash
cat > ./build.sh << EOF
#!/bin/bash
mkdir -p build
cd build
cmake ..
make -j\$(nproc)
EOF
chmod +x ./build.sh
```
