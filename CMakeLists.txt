cmake_minimum_required(VERSION 3.15)

project(acpp VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLOBAL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(GLOBAL_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(GLOBAL_TEST_DIR ${PROJECT_SOURCE_DIR}/test)
set(GLOBAL_VENDOR_DIR ${PROJECT_SOURCE_DIR}/vendor)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  SOURCE_DIR ${GLOBAL_VENDOR_DIR}/googletest
  DOWNLOAD_EXTRACT_TIMESTAMP OFF
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
include(GoogleTest)


# C++ primer
add_subdirectory(${GLOBAL_SOURCE_DIR}/primer)


file(GLOB_RECURSE TEST_SRC_FILES ${GLOBAL_TEST_DIR}/*.cpp)

# from list of files we'll create tests test_name.cpp -> test_name
foreach(_test_file ${TEST_SRC_FILES})
    message(STATUS ${_test_file})
    get_filename_component(_test_name ${_test_file} NAME_WE)
    add_executable(${_test_name} ${_test_file})
    target_link_libraries(
        ${_test_name}
        GTest::gtest_main
    )
    gtest_discover_tests(${_test_name})

    # add_dependencies(${_test_name} "googletest.git")
    # target_link_libraries(${_test_name} gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})
    # add_test(${_test_name} ${_test_name})
    # set_tests_properties(${_test_name} PROPERTIES TIMEOUT 5)
endforeach()