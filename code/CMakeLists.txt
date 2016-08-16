
# https://cmake.org/cmake/help/v3.0/command/include_directories.html
# The include directories are added to the INCLUDE_DIRECTORIES directory property for the current CMakeLists file. They are also added to the INCLUDE_DIRECTORIES target property for each target in the current CMakeLists file. The target property values are the ones used by the generators.
include_directories(${PROJECT_SOURCE_DIR}/code)

# library foundation
file(GLOB SOURCE_FILES_ 
    ${PROJECT_SOURCE_DIR}/code/foundation/*.h
	${PROJECT_SOURCE_DIR}/code/foundation/*.inl 
	${PROJECT_SOURCE_DIR}/code/foundation/*.c)
source_group("" FILES ${SOURCE_FILES_})

file(GLOB SOURCE_FILES_CORE 
    ${PROJECT_SOURCE_DIR}/code/foundation/core/*.h
	${PROJECT_SOURCE_DIR}/code/foundation/core/*.inl 
	${PROJECT_SOURCE_DIR}/code/foundation/core/*.c)
source_group("core" FILES ${SOURCE_FILES_CORE})

file(GLOB SOURCE_FILES_MEMORY 
    ${PROJECT_SOURCE_DIR}/code/foundation/memory/*.h
 	${PROJECT_SOURCE_DIR}/code/foundation/memory/*.inl 
	${PROJECT_SOURCE_DIR}/code/foundation/memory/*.c)
source_group("memory" FILES ${SOURCE_FILES_MEMORY})

file(GLOB SOURCE_FILES_PLATFORM 
    ${PROJECT_SOURCE_DIR}/code/foundation/platform/*.h 
	${PROJECT_SOURCE_DIR}/code/foundation/platform/*.inl 
	${PROJECT_SOURCE_DIR}/code/foundation/platform/*.c)
source_group("platform" FILES ${SOURCE_FILES_PLATFORM})

file(GLOB SOURCE_FILES_CONTAINER 
    ${PROJECT_SOURCE_DIR}/code/foundation/container/*.h 
	${PROJECT_SOURCE_DIR}/code/foundation/container/*.inl 
	${PROJECT_SOURCE_DIR}/code/foundation/container/*.c)
source_group("container" FILES ${SOURCE_FILES_CONTAINER})

add_library(foundation STATIC 
    ${SOURCE_FILES_}
    ${SOURCE_FILES_CORE}
    ${SOURCE_FILES_MEMORY}
    ${SOURCE_FILES_PLATFORM}
    ${SOURCE_FILES_CONTAINER}
    )

# library application
# aux_source_directory(${PROJECT_SOURCE_DIR}/code/application SRC_LIST)
# add_library(application STATIC ${SRC_LIST})

# library graphics
# aux_source_directory(${PROJECT_SOURCE_DIR}/code/graphics SRC_LIST)
# add_library(graphics STATIC ${SRC_LIST})

# librarys component
add_subdirectory(component)
