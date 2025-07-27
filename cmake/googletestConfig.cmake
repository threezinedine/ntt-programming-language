if (DEFINED_GTEST)
    return()
endif()
set(DEFINED_GTEST TRUE)

set(CMAKE_FOLDER "Externals")
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/externals/googletest 
    ${CMAKE_CURRENT_BINARY_DIR}/packages/googletest)
unset(CMAKE_FOLDER)