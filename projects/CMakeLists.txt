cmake_minimum_required(VERSION 3.2...4.2.1)

project(multi_project_project)

add_subdirectory(obuchaika)
add_subdirectory(shellsort)

set(CMAKE_SUPPRESS_REGENERATION true)

