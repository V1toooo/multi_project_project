project(long_number)

# Библиотека, а не исполняемый файл!
add_library(${PROJECT_NAME} STATIC long_number.cpp)

# Если нужен и исполняемый файл для тестов, добавь отдельно
# add_executable(${PROJECT_NAME}_demo long_number.cpp)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -finput-charset=UTF-8
        -fexec-charset=UTF-8
    )
endif()

# Нужно для подключения заголовков
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})