cmake_minimum_required(VERSION 3.10)

# Project name for tests (should be different from main project)
project(Kernel_Image_Tests)

enable_testing()
find_package(GTest REQUIRED)

add_executable(
    run_tests
    test_matrix.cpp
    test_image.cpp
)

target_include_directories(run_tests PUBLIC
    ${PROJECT_SOURCE_DIR}/include  # Corrected path
)

target_link_libraries(run_tests
    PRIVATE
    kernel_image  # Link to your core library
    GTest::GTest
    GTest::Main
)

add_test(NAME KernelImageTests COMMAND run_tests)
