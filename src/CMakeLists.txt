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
    ${PROJECT_SOURCE_DIR}/include
)

# Link the executable to the kernel_image library
target_link_libraries(myprogram kernel_image)

# Enable testing
enable_testing()

# Add test directory
add_subdirectory(${PROJECT_SOURCE_DIR}/test)
