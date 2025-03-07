cmake_minimum_required(VERSION 3.10)
project(Kernel_Image)

enable_testing()
find_package(GTest REQUIRED)

add_executable(
    run_tests
    test_matrix.cpp
    test_image.cpp
) 

target_include_directories(run_tests PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/core
)

target_link_libraries(run_tests 
    PRIVATE 
    kernel_image
    GTest::GTest 
    GTest::Main
)

add_test(NAME KernelImageTests COMMAND run_tests)
