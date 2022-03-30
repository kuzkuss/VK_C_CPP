cmake_minimum_required(VERSION 3.14)
project(tests)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES src/*.cpp)

file(GLOB SOURCES_TIME *.cpp ../src/utils.c)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

add_executable(time_test ${SOURCES_TIME})

target_include_directories(${PROJECT_NAME} PUBLIC ${POSTS_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${POSTS_LIB_LIBRARIES} GTest::Main)

target_include_directories(time_test PUBLIC ${POSTS_LIB_INCLUDE_DIRS} ../inc)
target_link_libraries(time_test ${POSTS_LIB_LIBRARIES})

