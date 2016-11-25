# c89
set(CMAKE_C_FLAGS "-Wall -Werror=declaration-after-statement -std=c99 -pedantic -Wno-c99-extensions -Wno-variadic-macros -Wno-unused-function")

# library-foundation
add_subdirectory(foundation)
# library-graphics
add_subdirectory(graphics)
# library-application
add_subdirectory(application)

# librarys component
add_subdirectory(component)
