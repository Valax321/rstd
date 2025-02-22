add_executable(test_string_append "string_append.cpp")
target_link_libraries(test_string_append rstd)

add_test(NAME string_append_string COMMAND test_string_append 0)
add_test(NAME string_append_charptr COMMAND test_string_append 1)
add_test(NAME string_append_fixed COMMAND test_string_append 2)
add_test(NAME string_length COMMAND test_string_append 3)
add_test(NAME string_size COMMAND test_string_append 4)
add_test(NAME string_ensure_size COMMAND test_string_append 5)
