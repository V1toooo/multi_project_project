project(obuchaika)

add_executable(${PROJECT_NAME} main.cpp menu_functions.cpp menu_items.cpp)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -finput-charset=UTF-8
        -fexec-charset=UTF-8
    )
endif()