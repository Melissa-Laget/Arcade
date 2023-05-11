cmake_minimum_required(VERSION 3.24)

project(arcade)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_COLOR_DIAGNOSTICS ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/lib)

add_subdirectory(interfaces)

add_subdirectory(menu)

add_subdirectory(libs/display/sfml)
add_subdirectory(libs/display/sdl2)
add_subdirectory(libs/display/ncurses)

add_subdirectory(libs/games/snake)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/internal)

add_library(${PROJECT_NAME}_lib STATIC src/arcade.cpp src/Core.cpp include/Core.hpp src/Lib.cpp include/Lib.hpp)

target_include_directories(${PROJECT_NAME}_lib PUBLIC include)
target_link_libraries(${PROJECT_NAME}_lib PUBLIC ${PROJECT_NAME}_interfaces)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)

target_compile_options(${PROJECT_NAME}_lib PRIVATE -fno-gnu-unique)

add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_menu)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.11.0
)
FetchContent_MakeAvailable(spdlog)
target_link_libraries(${PROJECT_NAME}_lib PUBLIC spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)

# script for deps graph
find_program(DOT_EXE "dot")
if (DOT_EXE)
    message(STATUS "dot found: ${DOT_EXE}")

    set(DOT_OUTPUT_TYPE "svg" CACHE STRING "Build a dependency graph. Options are dot output types: ps, png, pdf...")

    add_custom_target(dependency-graph
            COMMAND ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR} --graphviz=${CMAKE_BINARY_DIR}/graphviz/${PROJECT_NAME}.dot
            COMMAND ${DOT_EXE} -T${DOT_OUTPUT_TYPE} ${CMAKE_BINARY_DIR}/graphviz/${PROJECT_NAME}.dot -o ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.${DOT_OUTPUT_TYPE}
            )

    add_custom_command(
            TARGET dependency-graph POST_BUILD
            COMMAND ;
            COMMENT
            "Dependency graph generated and located at ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.${DOT_OUTPUT_TYPE}"
    )
else ()
    message(STATUS "dot not found!")
endif ()
