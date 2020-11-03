cmake_minimum_required(VERSION 3.17.3)

project(s4)

set(C_STANDARD C90)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/external/include)

find_package(OpenGL REQUIRED)

find_library(COCOA_LIBRARY Cocoa)
find_library(IOKIT_LIBRARY IOKit)

file(GLOB SOURCES src/*.c external/src/*.c)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -g -ansi -Wall -Wextra -Werror -pedantic -pedantic-errors -Wshadow -Wcast-align -Wwrite-strings)#-Wcast-qual

target_link_libraries(${CMAKE_PROJECT_NAME} OpenGL::GL)
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/external/lib/libglfw3.a)
target_link_libraries(${CMAKE_PROJECT_NAME} ${COCOA_LIBRARY})
target_link_libraries(${CMAKE_PROJECT_NAME} ${IOKIT_LIBRARY})
