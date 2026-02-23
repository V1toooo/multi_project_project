project(long_number)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} STATIC
    src/long_number.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${INCLUDE_DIR}
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -finput-charset=UTF-8
        -fexec-charset=UTF-8
    )
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests)
    add_subdirectory(tests)
endif()