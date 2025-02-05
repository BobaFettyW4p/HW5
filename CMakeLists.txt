cmake_minimum_required(VERSION 3.5)
project(HW5)
set(CMAKE_CXX_STANDARD 20)
find_package(Threads REQUIRED)

set(HEADERS ${CMAKE_SOURCE_DIR}/stack.h)

add_executable(HW5-1 HW5-1.cpp)
target_link_libraries(HW5-1 PRIVATE Threads::Threads)

add_executable(HW5-2 HW5-2.cpp)
target_link_libraries(HW5-2 PRIVATE Threads::Threads)

add_executable(HW5-3 HW5-3.cpp)
target_link_libraries(HW5-3 PRIVATE Threads::Threads)