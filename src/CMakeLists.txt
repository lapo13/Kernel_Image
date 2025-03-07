cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Kernel_Image)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create an executable
add_executable(Kernel_Image_main main.cpp)

# Define include directories
target_include_directories(Kernel_Image_main PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/core
)
