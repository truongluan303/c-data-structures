cmake_minimum_required(VERSION 3.0)

set(LIB_NAME data_structures)

# Define the library sources and headers
set(LIB_SOURCES
    src/vector.c
    )

# Create the library target
add_library(${LIB_NAME} SHARED ${LIB_SOURCES})

# Set the library version and soname properties
set_target_properties(${LIB_NAME} PROPERTIES
    OUTPUT_NAME ${LIB_NAME}
    EXPORT_NAME ${LIB_NAME}
    )

# Set the library include directories
target_include_directories(${LIB_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

# Set the library installation directories
install(TARGETS ${LIB_NAME}
    LIBRARY DESTINATION lib
    )
install(DIRECTORY "include/" DESTINATION include
    FILES_MATCHING PATTERN "*.h"
    )
