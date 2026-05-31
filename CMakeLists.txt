cmake_minimum_required(VERSION 3.20)

project(pingfinder-dataset VERSION 0.0.1)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_BUILD_TYPE Debug)

find_package(Qt6 REQUIRED COMPONENTS Core)

include_directories(${CMAKE_SOURCE_DIR}/src)

set(SOURCE_EXE main.cpp)

add_subdirectory(src)

add_executable(pingfinder-dataset ${SOURCE_EXE})

target_link_libraries(pingfinder-dataset PRIVATE Qt6::Core src-lib)
