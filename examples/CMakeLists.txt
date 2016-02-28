add_executable(basic_usage.t basic_usage.t.c)
target_link_libraries(basic_usage.t libtap13)

add_executable (skip_all.t skip_all.t.c)
target_link_libraries(skip_all.t libtap13)

add_executable (unknown_number_of_tests.t unknown_number_of_tests.t.c)
target_link_libraries (unknown_number_of_tests.t libtap13)
