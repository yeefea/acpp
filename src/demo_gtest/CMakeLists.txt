cmake_minimum_required(VERSION 3.10)

set(GLOBAL_VENDOR_DIR "../../../vendor")

message(STATUS "GoogleTest demo")

project(demo_gtest LANGUAGES CXX VERSION)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  SOURCE_DIR ${GLOBAL_VENDOR_DIR}/googletest
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  std_test
  std_test.cpp
)
target_link_libraries(
  std_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(std_test)