cmake_minimum_required(VERSION 3.10)
project(kernel_image_test VERSION 1.0)

# Debug prints
message(STATUS "Project source dir: ${PROJECT_SOURCE_DIR}")
message(STATUS "CMake source dir: ${CMAKE_SOURCE_DIR}")

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find GTest package with debug info
find_package(GTest REQUIRED)
message(STATUS "GTest include dirs: ${GTEST_INCLUDE_DIRS}")
message(STATUS "GTest libraries: ${GTEST_LIBRARIES}")

# Set source files for tests
set(TEST_SOURCES
    core/test_Image.cpp
    core/test_Matrix.cpp
    utils/test_ImageIO.cpp
    utils/test_Convolution.cpp
)

# Create test executable
add_executable(kernel_image_test 
    ${TEST_SOURCES}
    test_main.cpp
)

# Include directories
target_include_directories(kernel_image_test 
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${GTEST_INCLUDE_DIRS}
)

# Link test executable with Google Test and our library
target_link_libraries(kernel_image_test
    PRIVATE
    GTest::GTest
    GTest::Main
    kernel_image
)

enable_testing()
gtest_discover_tests(kernel_image_test)