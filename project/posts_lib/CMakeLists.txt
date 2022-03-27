cmake_minimum_required(VERSION 3.14)
project(posts_lib)

file(GLOB SOURCES src/*.c)
file(GLOB INCLUDE_DIRS inc)

if(PARALLEL)
    add_library(${PROJECT_NAME} ${SOURCES} src/count/parallel_count.c)
else()
    add_library(${PROJECT_NAME} ${SOURCES} src/count/sequential_count.c)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})

set(POSTS_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)

