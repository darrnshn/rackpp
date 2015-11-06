add_library(unit_test_main main.cpp)

add_executable(run_test_version version.cpp)
target_link_libraries(run_test_version gtest unit_test_main)
add_test(NAME version COMMAND run_test_version)
