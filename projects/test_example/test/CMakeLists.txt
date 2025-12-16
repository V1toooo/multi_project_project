add_executable(test_shellsort test_main.cpp)

target_sources(test_shellsort PRIVATE
    ../../shellsort/src/sort.cpp
    ../../shellsort/src/output.cpp
)

target_include_directories(test_shellsort PRIVATE
    ../../shellsort/src
)

target_link_libraries(test_shellsort
    gmock
    gtest
    gtest_main
)

enable_testing()
add_test(NAME ShellSortTest COMMAND test_shellsort)