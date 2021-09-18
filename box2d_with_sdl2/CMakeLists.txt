cmake_minimum_required(VERSION 3.20)
project(sdl2_with_input)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/SDL2-2.0.16/include)
set(BOX2D_INCLUDE_DIR  ${PROJECT_SOURCE_DIR}/box2d-master/include)
set(SDL2_LIB_DIR ${PROJECT_SOURCE_DIR}/SDL2-2.0.16/lib/x64)

# Support both 32 and 64 bit builds
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_LIBRARIES "${PROJECT_SOURCE_DIR}/SDL2-2.0.16/lib/x64/SDL2.lib;${PROJECT_SOURCE_DIR}/SDL2-2.0.16/lib/x64/SDL2main.lib")
else ()
    set(SDL2_LIBRARIES "${PROJECT_SOURCE_DIR}/SDL2-2.0.16/lib/x86/SDL2.lib;${PROJECT_SOURCE_DIR}/SDL2-2.0.16/lib/x86/SDL2main.lib")
endif ()

include_directories(${SDL2_INCLUDE_DIR} ${BOX2D_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${PROJECT_SOURCE_DIR}/box2d.lib)