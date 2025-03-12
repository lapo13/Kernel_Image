cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Kernel_Image)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create an executable
add_executable(myprogram main.cpp)

# Define include directories (relative to the project root)
target_include_directories(myprogram PUBLIC
    ${PROJECT_SOURCE_DIR}/include/core
    ${PROJECT_SOURCE_DIR}/include/utils
)

# Link the executable to the kernel_image library
target_link_libraries(myprogram kernel_image)
