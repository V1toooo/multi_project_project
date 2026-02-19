cmake_minimum_required(VERSION 3.2...4.2.1)

project(multi_project_project)

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(obuchaika)
add_subdirectory(shellsort)
add_subdirectory(test_example)
add_subdirectory(long_number)

set(CMAKE_SUPPRESS_REGENERATION true)