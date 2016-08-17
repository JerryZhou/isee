
# https://cmake.org/cmake/help/v3.0/command/include_directories.html
# The include directories are added to the INCLUDE_DIRECTORIES directory property for the current CMakeLists file. They are also added to the INCLUDE_DIRECTORIES target property for each target in the current CMakeLists file. The target property values are the ones used by the generators.
include_directories(${PROJECT_SOURCE_DIR}/code)

# library application
file(GLOB SOURCE_FILES_ 
    ${PROJECT_SOURCE_DIR}/code/application/*.h
	${PROJECT_SOURCE_DIR}/code/application/*.inl 
	${PROJECT_SOURCE_DIR}/code/application/*.c)
source_group("" FILES ${SOURCE_FILES_})

add_library(application STATIC 
    ${SOURCE_FILES_}
    )

