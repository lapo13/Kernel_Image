cmake_minimum_required(VERSION 3.10)

enable_testing()
find_package(GTest REQUIRED)

add_executable(run_tests 
    test_matrix.cpp
    test_channel.cpp
    test_image.cpp
)

target_link_libraries(run_tests 
    PRIVATE 
    kernel_image
    GTest::GTest 
    GTest::Main
)

add_test(NAME KernelImageTests COMMAND run_tests)