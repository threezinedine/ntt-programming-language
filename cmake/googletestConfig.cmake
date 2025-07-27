if (DEFINED_GTEST)
    return()
endif()
set(DEFINED_GTEST TRUE)

if (MSVC)
    set(CMAKE_FOLDER "Externals")
endif()

add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/externals/googletest 
    ${CMAKE_CURRENT_BINARY_DIR}/packages/googletest)

if (MSVC)
    unset(CMAKE_FOLDER)
endif()