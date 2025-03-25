cmake_minimum_required(VERSION 3.10)
project(Kernel_Image)

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
    src/core/Image.cpp
    src/core/Matrix.cpp
    src/core/Channel.cpp
    src/utils/ImageIO.cpp
    )

set(HEADER
    include/core/Image.h
    include/core/Matrix.h
    include/utils/ImageIO.h
)

# Crea la libreria kernel_image
add_library(kernel_image
        ${SOURCE}
        ${HEADER}
)

target_include_directories(kernel_image PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# Eseguibile principale
add_executable(myprogram src/main.cpp)
target_link_libraries(myprogram PRIVATE kernel_image)
target_include_directories(myprogram PRIVATE
        ${PROJECT_SOURCE_DIR}/include)

# ======= SEZIONE TEST =======
#enable_testing()  # Abilita CTest

# Aggiungi la sottodirectory dei test (dopo kernel_image!)
#add_subdirectory(tests)
