project(containers)

set(CONTAINERS_LIB "containers_lib")
add_library(${CONTAINERS_LIB} "")

add_subdirectory(src)
add_subdirectory(test)