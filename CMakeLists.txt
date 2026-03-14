cmake_minimum_required(VERSION 3.30)
project(wad
        DESCRIPTION "Simple, easy-to-use WAD interactions library"
        LANGUAGES C
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)

add_subdirectory("third_party/bytepicker")

add_library(wad)
target_link_libraries(wad PUBLIC bytepicker)
target_include_directories(wad PUBLIC "src")
target_sources(wad PRIVATE
        "src/wad/read/read.c"
)