
link_libraries(foundation application graphics glad glfw)

include_directories(${PROJECT_SOURCE_DIR}/code)
include_directories(${PROJECT_SOURCE_DIR}/depends)
include_directories(${PROJECT_SOURCE_DIR}/depends/glfw/include)

file(GLOB SOURCE_FILES_ 
    ${PROJECT_SOURCE_DIR}/example/01simplewindow/*.h
	${PROJECT_SOURCE_DIR}/example/01simplewindow/*.inl 
	${PROJECT_SOURCE_DIR}/example/01simplewindow/*.c)

# http://www.glfw.org/docs/3.0/build.html
# the GLFW_LIBRARIES cache variable contains all link-time dependencies of GLFW as it is currently configured
add_executable(isee-example-01simplewindow ${SOURCE_FILES_})
