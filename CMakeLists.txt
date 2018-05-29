cmake_minimum_required(VERSION 2.8)

project(parser)

set(SOURCE_EXE main.cpp)

set(SOURCE_LIB Tree.cpp)

find_package(Curses REQUIRED)

add_library(Tree STATIC ${SOURCE_LIB})

add_executable(main ${SOURCE_EXE})

include_directories(${CURSES_INCLUDE_DIR})

target_link_libraries(main Tree ${CURSES_LIBRARIES})
