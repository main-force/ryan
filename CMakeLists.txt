cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
project(ryan)

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/ncurses")
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_executable(RyanApplication application.cpp)
target_link_libraries(RyanApplication ${CURSES_LIBRARIES})

add_executable(RyanServer server.cpp World.cpp)