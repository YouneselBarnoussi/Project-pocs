cmake_minimum_required(VERSION 3.20)
project(conan)

set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(conan main.cpp)

target_link_libraries(conan ${CONAN_LIBS})
