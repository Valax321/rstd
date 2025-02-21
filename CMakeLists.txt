cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(rstd LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

option(RADISH_ENABLE_ASSERTIONS "Enable Assertions" ON)

if (${CMAKE_SOURCE_DIR} MATCHES ${CMAKE_CURRENT_SOURCE_DIR})
    option(RADISH_BUILD_TESTS "Build rstd tests" ON)
else()
    option(RADISH_BUILD_TESTS "Build rstd tests" OFF)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options("-fno-rtti" "-fno-exceptions")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options("/GR-" "/EHsc-")
endif()

if (RADISH_ENABLE_ASSERTIONS)
    add_compile_definitions("RADISH_ENABLE_ASSERTIONS=1")
endif()

set(RSTD_HDRS
"include/rstd/detail/debugbreak.h"
"include/rstd/hash/crc.hpp"
"include/rstd/hash/fnv1a.hpp"
"include/rstd/memory/heap.hpp"
"include/rstd/memory/malloc.hpp"
"include/rstd/assert.hpp"
"include/rstd/memory.hpp"
"include/rstd/rtti.hpp"
"include/rstd/string.hpp"
"include/rstd/types.hpp"
)

set(RSTD_SRCS
"src/assert.cpp"
"src/hash.cpp"
"src/memory.cpp"
"src/string.cpp"
)

add_library(rstd STATIC ${RSTD_SRCS} ${RSTD_HDRS})
target_include_directories(rstd PUBLIC "include" PRIVATE "src")

if (RADISH_BUILD_TESTS)
    message(STATUS "Building tests")
    enable_testing()
    add_subdirectory("tests")
endif()
