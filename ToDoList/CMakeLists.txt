# Imposta i file sorgente per la libreria
set(SOURCES
        iface.cpp
        TaskList.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
# Crea la libreria (può essere statica o condivisa)
add_library(ProgToDo_LIB ${SOURCES})

# Specifica la directory degli header (incluso json.hpp)
target_include_directories(ProgToDo_LIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})