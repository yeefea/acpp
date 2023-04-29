cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0097 NEW)

project(acpp VERSION 1.0)

cmake_host_system_information(RESULT OS_NAME QUERY OS_NAME)  # OS_NAME

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

set(GLOBAL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(GLOBAL_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(GLOBAL_TEST_DIR ${PROJECT_SOURCE_DIR}/test)
set(GLOBAL_VENDOR_DIR ${PROJECT_SOURCE_DIR}/vendor)
set(GLOBAL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)
set(GLOBAL_TOOLS_DIR ${PROJECT_SOURCE_DIR}/tools)

include_directories(${GLOBAL_INCLUDE_DIR})
link_directories(${GLOBAL_LIB_DIR})

file(GLOB THIRD_PARTY_LIST cmake/*.cmake)
foreach(THIRD_PARTY_LIB ${THIRD_PARTY_LIST})
  include (${THIRD_PARTY_LIB})
endforeach()

# C++ primer
add_subdirectory(${GLOBAL_SOURCE_DIR}/primer)
add_subdirectory(${GLOBAL_SOURCE_DIR}/effective)
add_subdirectory(${GLOBAL_SOURCE_DIR}/demo)

include(GoogleTest)

enable_testing()
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