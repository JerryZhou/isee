
# ************************************************************
# https://github.com/Dav1dde/glad
# http://glad.dav1d.de/
# load gl funcs
add_subdirectory(glad)

# ************************************************************
# glfw 3.2 http://www.glfw.org/download.html
# http://www.glfw.org/docs/latest/build_guide.html
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)
