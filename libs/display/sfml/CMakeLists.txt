cmake_minimum_required(VERSION 3.24)

project(${CMAKE_PROJECT_NAME}_display_sfml)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_COLOR_DIAGNOSTICS ON)


find_package(SFML REQUIRED COMPONENTS graphics window system)
include_directories(${SFML_INCLUDE_DIR})

add_library(${PROJECT_NAME} SHARED
        src/DisplaySfml.cpp
        )
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_PROJECT_NAME}_interfaces)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)

add_dependencies(${PROJECT_NAME} ${CMAKE_PROJECT_NAME}_interfaces)

add_executable(${PROJECT_NAME}_test EXCLUDE_FROM_ALL
        main.cpp
        )
target_link_libraries(${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME})
