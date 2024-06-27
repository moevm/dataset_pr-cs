cmake_minimum_required(VERSION 3.2)

project(Komarov_Daniil_cw)
set(EXE_NAME cw)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

# External libraries
find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

# Project code
add_executable(${EXE_NAME} main.c)

add_library(argdict     STATIC lib/argdict.c)
add_library(argparse    STATIC lib/argparse.c)
add_library(coord_queue STATIC lib/coord_queue.c)
add_library(drawing     STATIC lib/drawing.c)
add_library(errors      STATIC lib/errors.c)
add_library(image       STATIC lib/image.c)
add_library(pngfile     STATIC lib/pngfile.c)
add_library(set         STATIC lib/set.c)
add_library(tasks       STATIC lib/tasks.c)


target_link_libraries(argparse    argdict)
target_link_libraries(drawing     image)
target_link_libraries(drawing     coord_queue)
target_link_libraries(drawing     m)
target_link_libraries(image       set)
target_link_libraries(pngfile     ${PNG_LIBRARY})
target_link_libraries(tasks       image)
target_link_libraries(tasks       drawing)
target_link_libraries(tasks       pngfile)
target_link_libraries(${EXE_NAME} tasks)
target_link_libraries(${EXE_NAME} argparse)
target_link_libraries(${EXE_NAME} argdict)
target_link_libraries(${EXE_NAME} errors)
