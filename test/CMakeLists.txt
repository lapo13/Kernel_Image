cmake_minimum_required(VERSION 3.10)
project(kernel_image_test VERSION 1.0)

# Debug prints
message(STATUS "Project source dir: ${PROJECT_SOURCE_DIR}")
message(STATUS "CMake source dir: ${CMAKE_SOURCE_DIR}")

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Trova GTest
find_package(GTest REQUIRED)
message(STATUS "GTest include dirs: ${GTEST_INCLUDE_DIRS}")
message(STATUS "GTest libraries: ${GTEST_LIBRARIES}")

# File di test (solo header e main)
set(TEST_SOURCES
    core/test_Image.cpp
    core/test_Matrix.cpp
    utils/test_ImageIO.cpp
    utils/test_Convolution.cpp
    test_main.cpp
)

# Crea eseguibile per i test
add_executable(kernel_image_test ${TEST_SOURCES})

# Includi solo la cartella include (niente src)
target_include_directories(kernel_image_test 
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIRS}
)

# Linka GTest e la tua INTERFACE library
target_link_libraries(kernel_image_test
    PRIVATE
    GTest::GTest
    GTest::Main
    kernel_image
)

enable_testing()
gtest_discover_tests(kernel_image_test)