cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(rstd LANGUAGES C CXX)

include(GenerateExportHeader)

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

option(MI_OVERRIDE "" OFF)
option(MI_OPT_SIMD "" ON)
option(MI_BUILD_SHARED "" OFF)
option(MI_BUILD_TESTS "" OFF)
option(MI_BUILD_STATIC "" OFF)
add_subdirectory("vendor/mimalloc-3.0.1")

set(RSTD_HDRS
"include/rstd/containers/iterator.hpp"
"include/rstd/containers/vector.hpp"
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
generate_export_header(rstd EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/include/rstd/abi.hpp")
target_include_directories(rstd PUBLIC "include" "${CMAKE_CURRENT_BINARY_DIR}/include" PRIVATE "src")
target_link_libraries(rstd PRIVATE mimalloc-obj)

if (RADISH_BUILD_TESTS)
    message(STATUS "Building tests")
    enable_testing()
    add_subdirectory("tests")
endif()
