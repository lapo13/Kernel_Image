# Crea la libreria per il codice principale
add_library(core
    main.cpp
)

# Opzionale: crea un eseguibile
add_executable(main main.cpp)
target_link_libraries(main PRIVATE core)
