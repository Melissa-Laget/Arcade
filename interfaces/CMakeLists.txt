cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)

project(${CMAKE_PROJECT_NAME}_interfaces)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE .)
