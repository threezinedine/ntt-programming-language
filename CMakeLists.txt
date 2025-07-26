cmake_minimum_required(VERSION 3.15)

project(NTTLanguage)

file(
    GLOB
    INCLUDE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/nttlang/*.h
)

file(
    GLOB
    SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(
    ${PROJECT_NAME}
    ${INCLUDE_FILES}
    ${SOURCE_FILES}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)

file(
    GLOB
    TEST_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp
)

find_package(googletest REQUIRED)
set(TEST_PROJECT_NAME ${PROJECT_NAME}_test)
add_executable(${TEST_PROJECT_NAME} ${TEST_FILES})
target_link_libraries(${TEST_PROJECT_NAME} PRIVATE ${PROJECT_NAME} gtest gtest_main gmock gmock_main)