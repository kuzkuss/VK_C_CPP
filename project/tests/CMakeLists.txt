cmake_minimum_required(VERSION 3.14)
project(tests)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES src/*.cpp)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${AIRCRAFTS_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${AIRCRAFTS_LIB_LIBRARIES} GTest::Main)

