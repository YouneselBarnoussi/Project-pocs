cmake_minimum_required(VERSION 3.20)
project(hunter)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR C:/Users/youne/Desktop/Project-pocs/hunter/SDL2-2.0.16/include)
set(SDL2_LIB_DIR C:/Users/youne/Desktop/Project-pocs/hunter/SDL2-2.0.16/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(hunter main.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)