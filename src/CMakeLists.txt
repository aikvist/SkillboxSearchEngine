cmake_minimum_required(VERSION 3.23)

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(SearchEngine
        "SearchEngine.cpp"
        "ConverterJSON.cpp"
        "InvertedIndex.cpp"
        "SearchServer.cpp"
        "${MY_INCLUDE_DIR}/ConverterJSON.h"
       "${MY_INCLUDE_DIR}/InvertedIndex.h"
      "${MY_INCLUDE_DIR}/SearchServer.h"
)

target_include_directories(SearchEngine PUBLIC ${MY_INCLUDE_DIR})
