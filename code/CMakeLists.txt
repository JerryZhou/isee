
# https://cmake.org/cmake/help/v3.0/command/include_directories.html
# The include directories are added to the INCLUDE_DIRECTORIES directory property for the current CMakeLists file. They are also added to the INCLUDE_DIRECTORIES target property for each target in the current CMakeLists file. The target property values are the ones used by the generators.
include_directories(${PROJECT_SOURCE_DIR}/code)

# library foundation
aux_source_directory(${PROJECT_SOURCE_DIR}/code/foundation SRC_LIST)
file(GLOB HEAD_LIST ${PROJECT_SOURCE_DIR}/code/foundation/*.h)
add_library(foundation STATIC ${SRC_LIST} ${HEAD_LIST})

# library application
# aux_source_directory(${PROJECT_SOURCE_DIR}/code/application SRC_LIST)
# add_library(application STATIC ${SRC_LIST})

# library graphics
# aux_source_directory(${PROJECT_SOURCE_DIR}/code/graphics SRC_LIST)
# add_library(graphics STATIC ${SRC_LIST})

# librarys component
add_subdirectory(component)
