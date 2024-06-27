cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)

project(CW)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

add_executable(cw main.cpp)

target_include_directories(cw PUBLIC "include/")

add_library(image_redactor STATIC lib/ImageRedactor.cpp)
add_library(png_reader STATIC lib/PngReader.cpp)
add_library(line STATIC lib/Line.cpp)
add_library(circle STATIC lib/Circle.cpp)
add_library(rectangle STATIC lib/Rectangle.cpp)

target_link_libraries(cw image_redactor)
target_link_libraries(cw line)
target_link_libraries(cw circle)
target_link_libraries(cw rectangle)
target_link_libraries(cw png_reader)
target_link_libraries(png_reader ${PNG_LIBRARY})