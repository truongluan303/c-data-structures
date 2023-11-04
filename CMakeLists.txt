# Specify the minimum version.
cmake_minimum_required(VERSION 3.9)

# Specify the project info.
project(data_structures VERSION 1.0.0 DESCRIPTION "Data structures in C")

# Declare the library target.
add_library(${PROJECT_NAME} SHARED
    src/data_structures.h
    src/deque.h
    src/deque.c
    src/trie.h
    src/trie.c
    src/singly_linked_list.h
    src/singly_linked_list.c
    src/vector.h
    src/vector.c
)

# Configure the directories to search for header files.
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Set the public header property to the one with the actual API.
set(ALL_PUBLIC_HEADERS
    "src/data_structures.h"
    "src/deque.h"
    "src/trie.h"
    "src/singly_linked_list.h"
    "src/vector.h"
    )
set_target_properties(${PROJECT_NAME} PROPERTIES
    PUBLIC_HEADER "${ALL_PUBLIC_HEADERS}"
)

# For access to standard installation directory variables (CMAKE_INSTALL_xDIR).
include(GNUInstallDirs)

# Set library shared object and API header file to install.
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Create the pkg-config file from the template.
configure_file(src/${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)

# Set pkg-config file to install.
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)
