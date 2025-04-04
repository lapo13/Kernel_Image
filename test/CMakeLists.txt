cmake_minimum_required(VERSION 3.10)
project(kernel_image_test VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find GTest package
find_package(GTest REQUIRED)
include(GoogleTest)

# Set source files for tests
set(TEST_SOURCES
    ${PROJECT_SOURCE_DIR}/core/test_Image.cpp
    ${PROJECT_SOURCE_DIR}/core/test_Matrix.cpp
    ${PROJECT_SOURCE_DIR}/core/test_Channel.cpp
    ${PROJECT_SOURCE_DIR}/utils/test_ImageIO.cpp
    ${PROJECT_SOURCE_DIR}/utils/test_Convolution.cpp
)
# Set the main test source file
set(TEST_MAIN_SOURCE ${PROJECT_SOURCE_DIR}/test_main.cpp) # Assumendo che il file sia in test/

# Include directories for the library
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

# Set include directories for tests
include_directories(
    ${PROJECT_SOURCE_DIR}/test/core
    ${PROJECT_SOURCE_DIR}/test/utils
)

# Create test library
add_library(kernel_image_test_lib
    ${TEST_SOURCES}
)
# Add GTest include directory to the test library
target_include_directories(kernel_image_test_lib
    PRIVATE
    /opt/homebrew/include
)

# Create test executable
add_executable(kernel_image_test 
${TEST_MAIN_SOURCE}
)

# Link test executable with Google Test and our library
target_link_libraries(kernel_image_test
    PRIVATE
    kernel_image_test_lib
    GTest::GTest
    GTest::Main
    kernel_image
)

# Add tests to CTest
gtest_discover_tests(kernel_image_test)