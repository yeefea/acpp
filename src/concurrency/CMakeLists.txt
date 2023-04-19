cmake_minimum_required(VERSION 3.10)

set(GLOBAL_VENDOR_DIR "../../../vendor")

message(STATUS "C++ Concurrency Programming")

project(primer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(ch1 ch1.cpp)
add_executable(ch2 ch2.cpp)

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
#   ch1
#   ch1.cpp
# )
# target_link_libraries(
#   ch1
#   GTest::gtest_main
# )

# include(GoogleTest)
# gtest_discover_tests(ch1)