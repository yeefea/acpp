if(${OS_NAME} STREQUAL "Linux")

add_executable(demo_nanolog demo_nanolog.cpp)
target_link_libraries(demo_nanolog NanoLog)

endif()