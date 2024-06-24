cmake_minimum_required(VERSION 3.23)

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(MY_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

add_executable(GTests
        "test_first.cpp"
        "${MY_SOURCE_DIR}/InvertedIndex.cpp"
        "${MY_INCLUDE_DIR}/InvertedIndex.h"
         "test_second.cpp"
         "${MY_SOURCE_DIR}/SearchServer.cpp"
        "${MY_INCLUDE_DIR}/SearchServer.h"
)

target_link_libraries(GTests gtest_main)

include(GoogleTest)

gtest_discover_tests(GTests)

target_include_directories(GTests PUBLIC ${MY_INCLUDE_DIR})
target_include_directories(GTests PUBLIC ${MY_SOURCE_DIR})