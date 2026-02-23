add_executable(test_longnumber test_longnumber.cpp)

target_link_libraries(test_longnumber PRIVATE
    long_number
    gtest
    gtest_main
)

target_include_directories(test_longnumber PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

add_test(NAME LongNumberTest COMMAND test_longnumber)