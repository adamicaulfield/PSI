#
# Copyright SpiRITlab - Computations on Encrypted Data
# https://gitlab.com/SpiRITlab/coed
#

cmake_minimum_required(VERSION 3.15)
set(Project_Name PSI)
project(${Project_Name} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_VERBOSE_MAKEFILE on)

# output configurations
set(DEPS_ROOT ${PROJECT_SOURCE_DIR}/../../deps)
set(DEPS_INC_PATH ${DEPS_ROOT}/include)
set(DEPS_LIB_PATH ${DEPS_ROOT}/lib)
set(DEPS_BIN_PATH ${DEPS_ROOT}/bin)
set(DEPS_SRC_PATH ${DEPS_ROOT}/src)
set(DEPS_TMP_PATH ${DEPS_ROOT}/tmp)

include_directories(
        ${DEPS_ROOT}/include
        /usr/local/include)
link_directories(
        ${DEPS_ROOT}/lib
        /usr/local/lib)

add_custom_target(build-time-make-directory ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${DEPS_TMP_PATH}/keys"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${DEPS_TMP_PATH}/records")

# Output configurations
set(LIBRARY_OUTPUT_PATH ${DEPS_LIB_PATH})
set(EXECUTABLE_OUTPUT_PATH ${DEPS_BIN_PATH})
set(TEST_OUTPUT_PATH ${DEPS_TMP_PATH})

# Input configuration
set(SOURCES_DIR ${PROJECT_SOURCE_DIR})
set(SOURCE_FILES
        Encryptor.cpp
        FileSystem.cpp
        Util.cpp
        BasicExamples.cpp
        PSI.cpp)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

set_source_files_properties(${SOURCE_FILES} PROPERTIES LANGUAGE CXX)
add_executable(${Project_Name} main.cpp ${SOURCE_FILES})
target_link_libraries(${Project_Name} m helib ntl pthread gmp)