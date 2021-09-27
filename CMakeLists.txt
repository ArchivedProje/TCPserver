cmake_minimum_required(VERSION 3.16)

include("cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.314.tar.gz"
        SHA1 "95c47c92f68edb091b5d6d18924baabe02a6962a"
)

project(TCPserver)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_library(Network STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Network/sources/HandleConnection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Network/sources/Server.cpp
        )

target_include_directories(Network PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Network/include>
        $<INSTALL_INTERFACE:include>
        )

add_library(Logging STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Logging/sources/Logger.cpp
        )

target_include_directories(Logging PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Logging/include>
        $<INSTALL_INTERFACE:include>
        )

file(COPY Logging/log DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

hunter_add_package(nlohmann_json)
find_package(nlohmann_json REQUIRED)

hunter_add_package(Boost COMPONENTS system)
find_package(Boost COMPONENTS system REQUIRED)

target_link_libraries(Network Logging Boost::system nlohmann_json::nlohmann_json)

add_executable(demo demo/main.cpp)

target_link_libraries(demo Network)
