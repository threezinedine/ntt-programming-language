cmake_minimum_required(VERSION 3.15)

project(NTTLanguage)

if (MSVC)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

file(
    GLOB
    INCLUDE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/nttlang/*.h
)

if (NOT MSVC)
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -g)
endif()

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

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
endif()

if (MSVC)
    add_compile_definitions(MSVC)
elseif (MINGW)
    add_compile_definitions(MINGW)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
if (MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Core")
endif()

file(
    GLOB
    TEST_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp
)

find_package(googletest REQUIRED)
set(TEST_PROJECT_NAME ${PROJECT_NAME}_test)
add_executable(${TEST_PROJECT_NAME} ${TEST_FILES})
target_link_libraries(${TEST_PROJECT_NAME} PRIVATE ${PROJECT_NAME} gtest gtest_main gmock gmock_main)
if (MSVC)
    set_target_properties(${TEST_PROJECT_NAME} PROPERTIES FOLDER "Tests")
endif()

# add examples 
file(
    GLOB
    EXAMPLE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp
)

set(IS_FIRST_EXAMPLE TRUE)

foreach(EXAMPLE_FILE ${EXAMPLE_FILES})
    # extract file name without extension
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_FILE} NAME_WE)

    add_executable(${EXAMPLE_NAME} ${EXAMPLE_FILE})
    target_link_libraries(${EXAMPLE_NAME} PRIVATE ${PROJECT_NAME})

    if(MSVC)
        set_target_properties(${EXAMPLE_NAME} PROPERTIES FOLDER "Examples")
        if (IS_FIRST_EXAMPLE)
            set(IS_FIRST_EXAMPLE FALSE)
            set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${EXAMPLE_NAME})
            message(STATUS "Set ${EXAMPLE_NAME} as startup project")
        endif()
    endif()
endforeach()
