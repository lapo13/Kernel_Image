cmake_minimum_required(VERSION 3.10)
project(kernel_image VERSION 1.0)

# Imposta standard C++ e opzioni
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Imposta le opzioni di compilazione
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")

# Imposta i sanitizers
set(CMAKE_CXX_FLAGS_DEBUG "-g -fsanitize=address,undefined -fno-omit-frame-pointer")
set(CMAKE_LINKER_FLAGS_DEBUG "-fsanitize=address,undefined")

# Imposta dei nominativi per i file sorgente e header
set (SOURCE 
    src/core/Channel.cpp
    src/utils/Convolution_Engine.cpp
    )

set(HEADER
    include/core/Image.h
    include/core/Matrix.h
    include/core/Channel.h
    include/utils/ImageIO.h
    include/ImageHeader.h
    include/utils/Convolution_Engine.h
)

# Crea la libreria kernel_image
add_library(kernel_image
        ${SOURCE}
        ${HEADER}
)

# Linka la libreria kernel_image con le librerie necessarie
target_include_directories(kernel_image PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)

# Eseguibile principale
add_executable(myprogram src/main.cpp)
target_link_libraries(myprogram PRIVATE kernel_image)

# ======= SEZIONE TEST =======
enable_testing()  # Abilita CTest
add_subdirectory(test)

