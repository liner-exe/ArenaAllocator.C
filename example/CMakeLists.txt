cmake_minimum_required(VERSION 3.14)
project(ArenaAllocator LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(lnr_arena INTERFACE)

target_include_directories(lnr_arena INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:include>
)

add_executable(arena_example main.c)

target_link_libraries(arena_example PRIVATE lnr_arena)