if(${OS_NAME} STREQUAL "Linux")

add_executable(demo_nanolog demo_nanolog.cpp)
target_link_libraries(demo_nanolog NanoLog)

endif()

add_executable(demo_ws demo_ws.cpp)

target_link_libraries(demo_ws
  boost_system
)

add_executable(demo_wss demo_wss.cpp)

target_link_libraries(demo_wss
  crypto
  ssl
  boost_system
)

add_executable(demo_boost_asio demo_boost_asio.cpp)
target_link_libraries(demo_boost_asio
  boost_system
  boost_thread
)


add_executable(sync_daytime_client sync_daytime_client.cpp)
target_link_libraries(sync_daytime_client
  boost_system
)
add_executable(sync_daytime_server sync_daytime_server.cpp)
target_link_libraries(sync_daytime_server
  boost_system
)

add_executable(async_daytime_server async_daytime_server.cpp)
target_link_libraries(async_daytime_server
  boost_system
)

add_executable(demo_raii demo_raii.cpp)

add_executable(demo_shm_write
  demo_shm_write.cpp
)

add_executable(demo_shm_read
  demo_shm_read.cpp
)

add_executable(demo_thread demo_thread.cpp)