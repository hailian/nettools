add_executable(UdpServerTest UdpServerTest.cpp)
target_link_libraries(UdpServerTest ${Boost_LIBRARIES})

add_executable(UdpClientTest UdpClientTest.cpp)
target_link_libraries(UdpClientTest ${Boost_LIBRARIES})
