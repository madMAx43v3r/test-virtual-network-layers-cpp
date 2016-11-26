
include_directories(./)

add_executable(test_stuff test_stuff.cpp)
target_link_libraries(test_stuff)

add_executable(test_module test_module.cpp)
target_link_libraries(test_module vnl vni)

add_executable(test_type_stream test_type_stream.cpp)
target_link_libraries(test_type_stream vnl vni)

add_executable(test_packet test_packet.cpp)
target_link_libraries(test_packet vnl vni)

add_executable(test_tcp_server test_tcp_server.cpp)
target_link_libraries(test_tcp_server vnl vni)

add_executable(test_tcp_client test_tcp_client.cpp)
target_link_libraries(test_tcp_client vnl vni)

add_executable(test_database test_database.cpp)
target_link_libraries(test_database vnl vni)



