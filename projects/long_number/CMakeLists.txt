project(long_number)

add_library(${PROJECT_NAME} STATIC long_number.cpp)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -finput-charset=UTF-8
        -fexec-charset=UTF-8
    )
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})