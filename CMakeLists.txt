# Specify the minimum version.
cmake_minimum_required(VERSION 3.9)

# Specify the project info.
project(data_structures VERSION 1.0.0 DESCRIPTION "Data structures in C")

# Declare the library target.
add_library(${PROJECT_NAME} SHARED
    src/data_structures.h
    src/deque/deque.h
    src/deque/deque.c
    src/heap/heap.h
    src/heap/heap.c
    src/linkedlist/singly_linked_list.h
    src/linkedlist/singly_linked_list.c
    src/vector/vector.h
    src/vector/vector.c
)

# Configure the directories to search for header files.
target_include_directories(${PROJECT_NAME} PRIVATE source)

# Set the version property.
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

# Set the shared object version property to the project's major version.
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

# Set the public header property to the one with the actual API.
set(ALL_PUBLIC_HEADERS
    "src/data_structures.h"
    "src/deque/deque.h"
    "src/heap/heap.h"
    "src/linkedlist/singly_linked_list.h"
    "src/vector/vector.h"
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
