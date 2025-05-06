cmake_minimum_required(VERSION 3.10)
project(club_handler)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(club_handler ${SOURCES})
target_link_libraries(club_handler)

add_subdirectory(test)