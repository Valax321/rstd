add_library(rstd_test STATIC "rstd_test.hpp" "rstd_test.cpp")
target_include_directories(rstd_test PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(rstd_test rstd)
