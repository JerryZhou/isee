include_directories(${PROJECT_SOURCE_DIR}/code)
include_directories(${PROJECT_SOURCE_DIR}/test)

# test-foundation
aux_source_directory(${PROJECT_SOURCE_DIR}/test SRC_LIST)
file(GLOB HEAD_LIST_FOUNDATION ${PROJECT_SOURCE_DIR}/test/foundation/*.h)
file(GLOB HEAD_LIST_APPLICATION ${PROJECT_SOURCE_DIR}/test/application/*.h)
file(GLOB HEAD_LIST_GRAPHICS ${PROJECT_SOURCE_DIR}/test/graphics/*.h)
add_executable(isee-test-foundation ${SRC_LIST} 
    ${HEAD_LIST_FOUNDATION} 
    ${HEAD_LIST_APPLICATION} 
    ${HEAD_LIST_GRAPHICS})
target_link_libraries(isee-test-foundation foundation)
