cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 14)

project(ryan)

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt5/lib/cmake/")

find_package(Qt5Widgets REQUIRED)

add_executable(ryan main.cpp)
target_link_libraries(ryan Qt5::Widgets)