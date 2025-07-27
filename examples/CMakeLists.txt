file(
    GLOB
    EXAMPLE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

foreach(EXAMPLE_FILE ${EXAMPLE_FILES})
    # extract file name without extension
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_FILE} NAME_WE)

    add_executable(${EXAMPLE_NAME} ${EXAMPLE_FILE})
    target_link_libraries(${EXAMPLE_NAME} PRIVATE ${PROJECT_NAME})

    set_target_properties(${EXAMPLE_NAME} PROPERTIES FOLDER "Examples")
endforeach()

