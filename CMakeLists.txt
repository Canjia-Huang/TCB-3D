cmake_minimum_required (VERSION 3.8)

project("TCB3D")

# set publish bin location
set(PUBLISH_BIN_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/build/bin/debug)
set(PUBLISH_BIN_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/build/bin/release)
# set runtime output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PUBLISH_BIN_DEBUG})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PUBLISH_BIN_RELEASE})
# set output file directory
add_compile_definitions(TCB_VERBOSE) # use to verbose
add_compile_definitions(OUTPUT_PATH="${PROJECT_SOURCE_DIR}/data/")

# Eigen
find_package(Eigen3 REQUIRED)
IF(Eigen3_FOUND)
    message(STATUS "Eigen3 FOUNDED ${EIGEN3_VERSION_STRING} ${EIGEN3_INCLUDE_DIR}")
    include_directories(${EIGEN3_INCLUDE_DIR})
ELSE()
    message(FATAL_ERROR "Eigen3 NOT FOUNDED")
ENDIF()

# add libraries directory
include_directories(${PROJECT_SOURCE_DIR}/external)
include_directories(${PROJECT_SOURCE_DIR}/src)

# add source file directory
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_SOURCE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/tetrahedralization TETRAHEDRALIZATION_SRC_SOURCE)
aux_source_directory(${PROJECT_SOURCE_DIR}/external EXTERNAL_SRC_SOURCE)
add_executable(TCB3D ${SRC_SOURCE} ${TETRAHEDRALIZATION_SRC_SOURCE} ${EXTERNAL_SRC_SOURCE})