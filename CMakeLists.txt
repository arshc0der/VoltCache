cmake_minimum_required(VERSION 3.10)
project(VoltCache)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)

if(WIN32)
    set(NET_LIBS ws2_32)
endif()

add_executable(VoltCache src/main.cpp src/VoltCache.cpp)
target_link_libraries(VoltCache ${NET_LIBS})