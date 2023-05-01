if(${OS_NAME} STREQUAL "Linux")

add_executable(demo_nanolog demo_nanolog.cpp)
target_link_libraries(demo_nanolog NanoLog)

endif()

add_executable(demo_ws demo_ws.cpp)

target_link_libraries(demo_ws
  boost_system
)

add_executable(demo_boost_asio demo_boost_asio.cpp)
target_link_libraries(demo_boost_asio
  boost_system
  boost_thread
)
