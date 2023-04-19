cmake_minimum_required(VERSION 3.10)

project(ACPP)

set(GLOBAL_INCLUDE_DIR "../../include")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(ch1 ch1.cpp)
add_executable(ch2 ch2.cpp)
add_executable(ch3 ch3.cpp)
add_executable(ch4 ch4.cpp Student_info.cpp grade.cpp median.cpp)
add_executable(ch5 ch5.cpp Student_info.cpp median.cpp grade.cpp util.cpp)
add_executable(ch6 ch6.cpp Student_info.cpp median.cpp grade.cpp util.cpp)

target_include_directories(ch4 PUBLIC ${GLOBAL_INCLUDE_DIR})
target_include_directories(ch5 PUBLIC ${GLOBAL_INCLUDE_DIR})
target_include_directories(ch6 PUBLIC ${GLOBAL_INCLUDE_DIR})