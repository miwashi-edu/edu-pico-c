# edu-pico-c

```bash
cd ~
cd ws
mkdir mycppproject && cd mycppproject
mkdir -p ./{src,include,lib,tests,build}
echo "target_link_libraries(\mycppproject PRIVATE my_lib)" >> ./src/CMakeLists.txt
chmod +x ./build.sh"

# Print success message
echo "✅ C++ CMake project mycppproject created successfully!"
echo "➡️  Run './build.sh' to build the project."
```

```bash
# Create the main CMakeLists.txt
cat > "$PROJECT_NAME/CMakeLists.txt" << EOF
cmake_minimum_required(VERSION 3.16)
project($PROJECT_NAME LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(tests)

enable_testing()
EOF
```

```bash
# Create lib/CMakeLists.txt for the library
cat > "$PROJECT_NAME/lib/CMakeLists.txt" << EOF
add_library(my_lib my_lib.cpp)
target_include_directories(my_lib PUBLIC \${PROJECT_SOURCE_DIR}/include)
EOF
```

```bash
# Create library header file
cat > "$PROJECT_NAME/include/my_lib.h" << EOF
#ifndef MY_LIB_H
#define MY_LIB_H

#include <string>

std::string my_function();

#endif // MY_LIB_H
EOF

# Create library implementation file
cat > "$PROJECT_NAME/lib/my_lib.cpp" << EOF
#include "my_lib.h"

std::string my_function() {
return "Hello from my_lib!";
}
EOF
```

```bash
cat > "$PROJECT_NAME/tests/CMakeLists.txt" << EOF
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
cat > "$PROJECT_NAME/tests/test_main.cpp" << EOF
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
# Create a .gitignore file
cat > "$PROJECT_NAME/.gitignore" << EOF
/build/
/CMakeCache.txt
/CMakeFiles/
/cmake_install.cmake
/Makefile
EOF
```

```bash
# Create src/CMakeLists.txt for the main executable
cat > "$PROJECT_NAME/src/CMakeLists.txt" << EOF
add_executable(\${PROJECT_NAME} main.cpp)
target_include_directories(\${PROJECT_NAME} PRIVATE \${PROJECT_SOURCE_DIR}/include)
EOF

# Create main.cpp
cat > "$PROJECT_NAME/src/main.cpp" << EOF
#include <iostream>
#include "my_lib.h"

int main() {
std::cout << "Hello from $PROJECT_NAME!" << std::endl;
std::cout << "Library says: " << my_function() << std::endl;
return 0;
}
EOF
```

```bash
# Create a build script
cat > "$PROJECT_NAME/build.sh" << EOF
#!/bin/bash
mkdir -p build
cd build
cmake ..
make -j\$(nproc)
EOF
```