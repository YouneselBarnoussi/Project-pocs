cmake_minimum_required(VERSION 3.20)
project(vcpkg)

set(CMAKE_CXX_STANDARD 14)

add_executable(vcpkg main.cpp)

find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(ZLIB REQUIRED)
find_package(fmt CONFIG REQUIRED)
target_link_libraries(vcpkg PRIVATE unofficial::sqlite3::sqlite3 ZLIB::ZLIB fmt::fmt)
