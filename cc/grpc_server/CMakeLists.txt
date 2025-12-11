cmake_minimum_required(VERSION 3.15)
project(grpc_server)

set(CMAKE_CXX_STANDARD 17)

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})

# Proto-Datei
set(PROTO proto/hello_world.proto)
protobuf_generate_cpp(PROTO_SRC PROTO_HDR ${PROTO})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(server src/server.cpp ${PROTO_SRC} ${PROTO_HDR})
target_link_libraries(server ${Protobuf_LIBRARIES})

add_executable(client src/client.cpp ${PROTO_SRC} ${PROTO_HDR})
target_link_libraries(client ${Protobuf_LIBRARIES})