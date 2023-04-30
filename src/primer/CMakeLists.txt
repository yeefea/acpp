cmake_minimum_required(VERSION 3.10)

set(PRIMER_VERSION "5.0")
set(GLOBAL_VENDOR_DIR "../../../vendor")

message(STATUS "C++ Primer version: ${PRIMER_VERSION}")

# project(primer LANGUAGES CXX VERSION ${PRIMER_VERSION})

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)
add_executable(primer_ch1 ch1.cpp)
add_executable(primer_ch3 ch3_string.cpp)
add_executable(primer_ch4 ch4_expression.cpp utils.cpp)
add_executable(primer_ch9 ch9_seq_container.cpp)
add_executable(primer_ch10 ch10_algorithm.cpp)
add_executable(primer_ch11 ch11_assoc_container.cpp)
add_executable(primer_ch12 ch12_dynamic_memory.cpp utils.cpp str_blob.cpp str_blob_ptr.cpp text_query.cpp query_result.cpp)
add_executable(primer_ch19 ch19_special_tools.cpp)

# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
#   SOURCE_DIR ${GLOBAL_VENDOR_DIR}
# )
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

# enable_testing()

# add_executable(
#   hello_test
#   hello_test.cpp
# )
# target_link_libraries(
#   hello_test
#   GTest::gtest_main
# )

# include(GoogleTest)
# gtest_discover_tests(hello_test)