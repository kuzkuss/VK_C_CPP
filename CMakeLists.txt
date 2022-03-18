cmake_minimum_required(VERSION 3.14)
project(hw1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -Werror -Wpedantic")

option(LINTERS "Enable linters" ON)
option(WITH_MEMCHECK "Enable memory check" ON)
option(TESTING "Enable unit testing" OFF)
option(COVERAGE "Enable code coverage measurement" OFF)
option(SANITIZERS "Enable sanitizers" OFF)

if (COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage -fPIC -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -O0")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")
endif(COVERAGE)

if(SANITIZERS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error")
endif(SANITIZERS)

add_subdirectory(project/aircrafts_lib)
add_executable(${PROJECT_NAME} project/main.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${AIRCRAFTS_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${AIRCRAFTS_LIB_LIBRARIES})

add_subdirectory(project/tests)

if(WITH_MEMCHECK)
    add_custom_target(memcheck ALL COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/memtest.sh
                                            ${CMAKE_CURRENT_SOURCE_DIR}/build/project/tests/tests
                                    DEPENDS tests)
endif(WITH_MEMCHECK)

if(TESTING)
    add_custom_target(test ALL COMMAND tests)
endif(TESTING)

if(LINTERS)
    add_custom_target(check ALL COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/linters/run.sh)
endif(LINTERS)

