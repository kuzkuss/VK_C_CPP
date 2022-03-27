cmake_minimum_required(VERSION 3.14)
project(hw2)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Wextra -Werror -Wpedantic")

option(LINTERS "Enable linters" ON)
option(WITH_MEMCHECK "Enable memory check" ON)
option(TESTING "Enable unit testing" OFF)
option(COVERAGE "Enable code coverage measurement" OFF)
option(SANITIZERS "Enable sanitizers" OFF)
option(PARALLEL "Enable parallel algorithm" OFF)

if (COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage -fPIC -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -O0")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")
endif()

if(SANITIZERS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error")
endif()

add_subdirectory(project/posts_lib)

add_executable(${PROJECT_NAME} project/src/main.c project/src/utils.c)

target_link_libraries(${PROJECT_NAME} PRIVATE ${POSTS_LIB_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC project/inc)

#add_subdirectory(project/tests)

if(WITH_MEMCHECK)
    add_custom_target(memcheck ALL COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/memtest.sh
                                            ${CMAKE_CURRENT_SOURCE_DIR}/build/project/tests/tests
                                    DEPENDS tests)
endif()

if(TESTING)
    add_custom_target(test ALL COMMAND tests)
endif()

if(LINTERS)
    add_custom_target(check ALL COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/linters/run.sh)
endif()

