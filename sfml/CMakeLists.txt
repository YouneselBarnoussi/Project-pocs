cmake_minimum_required(VERSION 3.20)
project(sfml)

set(CMAKE_CXX_STANDARD 14)

set(SFML_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/SFML-2.5.1/include)

set(SFML_ROOT ${PROJECT_SOURCE_DIR}/SFML-2.5.1)

add_executable(${PROJECT_NAME} main.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2 REQUIRED graphics window network audio system)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()
