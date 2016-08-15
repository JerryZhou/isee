include_directories(${PROJECT_SOURCE_DIR}/code)

# test-foundation
aux_source_directory(${PROJECT_SOURCE_DIR}/test SRC_LIST)
add_executable(isee-test-foundation ${SRC_LIST})
