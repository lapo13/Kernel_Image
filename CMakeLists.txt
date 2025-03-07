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

# Aggiungi la libreria principale
add_subdirectory(src)

# Aggiungi i test
enable_testing()
add_subdirectory(test)
