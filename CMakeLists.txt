cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 14)
project(ryan)

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/ncurses")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(ryan main.cpp)
target_link_libraries(ryan ${CURSES_LIBRARIES})