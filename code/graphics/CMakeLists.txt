
# https://cmake.org/cmake/help/v3.0/command/include_directories.html
# The include directories are added to the INCLUDE_DIRECTORIES directory property for the current CMakeLists file. They are also added to the INCLUDE_DIRECTORIES target property for each target in the current CMakeLists file. The target property values are the ones used by the generators.
include_directories(${PROJECT_SOURCE_DIR}/code)
include_directories(${PROJECT_SOURCE_DIR}/depends/glfw/include)

# library graphics
file(GLOB SOURCE_FILES_ 
    ${PROJECT_SOURCE_DIR}/code/graphics/*.h
	${PROJECT_SOURCE_DIR}/code/graphics/*.inl 
	${PROJECT_SOURCE_DIR}/code/graphics/*.c)
source_group("" FILES ${SOURCE_FILES_})

add_library(graphics STATIC 
    ${SOURCE_FILES_}
    )

