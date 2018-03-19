cmake_minimum_required(VERSION 2.8.9)
set (CMAKE_CXX_STANDARD 11)
project (Threader)
include_directories(include)

find_package (Threads)
find_package (Curses REQUIRED)
file(GLOB SOURCES "src/*.cpp")

add_executable(Threader ${SOURCES})
target_link_libraries (Threader ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (Threader ${CURSES_LIBRARIES})