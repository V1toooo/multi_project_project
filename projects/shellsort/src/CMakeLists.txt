target_sources(shellsort
    PRIVATE 
        output.cpp
        output.hpp
        sort.cpp
        sort.hpp
)

target_include_directories(shellsort PRIVATE
    "${PROJECT_SOURCE_DIR}/src"
)