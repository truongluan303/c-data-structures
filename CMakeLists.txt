cmake_minimum_required(VERSION 3.14)

set(OUTLIBNAME "${BASENAME}") # outfile name: lib${OUTLIBNAME}.so
set(LIBNAME "${BASENAME}") # cmake target name
set(LIBALIAS  "${BASENAME}") # import target name

# Useful debug info if there are cmake linking issues.
message(STATUS "CMake Target: ${LIBNAME}")
message(STATUS "CMake Alias : ${LIBALIAS}")
message(STATUS "Output File : lib${OUTLIBNAME}.[a|so]")

project(${LIBNAME} C CXX)

set(LIB_SOURCES
    src/hashtable.c
    src/queue.c
    src/vector.c
    )

set_target_properties(${LIBNAME}
    PROPERTIES
    OUTPUT_NAME ${OUTLIBNAME}
    # Aliases can be used in the same env but are not exportable.
    EXPORT_NAME ${LIBALIAS}
    )

target_include_directories(${LIBNAME}
    PRIVATE
    src
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/>
    )

#########################
# Install headers/cmake #
#########################

install(TARGETS ${LIBNAME}
    EXPORT ${LIBNAME}_export
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(DIRECTORY "include/" DESTINATION include/ COMPONENT lib_data_structures_headers
    FILES_MATCHING PATTERN "*.h"
    )

install(EXPORT ${LIBNAME}_export
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIBNAME}
    FILE        ${LIBNAME}Targets.cmake
    )

install(FILES ${LIBNAME}Config.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIBNAME})
