cmake_minimum_required(VERSION 3.24)

project(${CMAKE_PROJECT_NAME}_display_sdl2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_COLOR_DIAGNOSTICS ON)


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED
        src/DisplaySdl2.cpp
        )
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_PROJECT_NAME}_interfaces)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})

add_dependencies(${PROJECT_NAME} ${CMAKE_PROJECT_NAME}_interfaces)

add_executable(${PROJECT_NAME}_test EXCLUDE_FROM_ALL
        main.cpp
        )
target_link_libraries(${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME})
