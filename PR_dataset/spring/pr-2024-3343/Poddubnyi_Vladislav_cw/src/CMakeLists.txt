cmake_minimum_required(VERSION 3.13)
project(Poddubnyi_Vladislav_cw)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES source/main.cpp
        source/opts_reader.cpp
        source/image_processor.cpp
        source/picture.cpp
)

add_executable(Poddubnyi_Vladislav_cw ${SOURCE_FILES})