if (DEFINED_GTEST)
    return()
endif()
set(DEFINED_GTEST TRUE)

add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/externals/googletest 
    ${CMAKE_CURRENT_BINARY_DIR}/packages/googletest)