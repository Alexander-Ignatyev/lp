cmake_minimum_required(VERSION 2.6)
enable_language(CXX)

project(lp)

include_directories(src)

# LP library
file(GLOB LPLIB_SRC src/lplib/*.cpp)
add_library(lplib STATIC ${LPLIB_SRC})

# Homework 2.1
add_executable(homework21 src/homework21/main.cpp)
target_link_libraries(homework21 lplib)

# Homework 2.2
add_executable(homework22 src/homework22/main.cpp)
target_link_libraries(homework22 lplib)

# Homework 3.1
add_executable(homework31 src/homework31/main.cpp)
target_link_libraries(homework31 lplib)

# Homework 6.1
add_executable(homework61 src/homework61/main.cpp)
target_link_libraries(homework61 lplib)
