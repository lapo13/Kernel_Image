cmake_minimum_required(VERSION 3.10)
project(Kernel_Image VERSION 1.0)

# Specifica lo standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Opzioni di compilazione
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif(MSVC)
    add_compile_options(/W4)
endif()

set(CMAKE_BUILD_TYPE Debug)

# Aggiungi la directory include
include_directories(${PROJECT_SOURCE_DIR}/include)

# Create a library for the core code
add_library(kernel_image
    src/core/Image.cpp
    src/core/Matrix.cpp
    src/utils/ImageIO.cpp
)

# Group source files for better organization
source_group(Core FILES
    src/core/Image.cpp
    src/core/Matrix.cpp
)

source_group(Utils FILES
    src/utils/ImageIO.cpp
)

# Link the library to the executable
add_executable(myprogram src/main.cpp)
target_link_libraries(myprogram kernel_image)

# Aggiungi i test
#enable_testing()
#add_subdirectory(test)
