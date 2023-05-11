cmake_minimum_required(VERSION 3.24)

project(${CMAKE_PROJECT_NAME}_game_snake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_COLOR_DIAGNOSTICS ON)

add_library(${PROJECT_NAME} SHARED
        src/GameSnake.cpp
        )
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_PROJECT_NAME}_interfaces)

add_dependencies(${PROJECT_NAME} ${CMAKE_PROJECT_NAME}_interfaces)