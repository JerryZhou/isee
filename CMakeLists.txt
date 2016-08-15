# version needed
cmake_minimum_required (VERSION 2.8)
# c89
set(CMAKE_C_FLAGS "-O2 -Wall -Werror=declaration-after-statement -std=c89 -pedantic -Dinline='' -Wno-c99-extensions -Wno-variadic-macros -Wno-unused-function")
# fix the compile-problem in mac-osx
set(CMAKE_MACOSX_RPATH 1)

# project declare
project(isee)

# all librarys
add_subdirectory(code)

# all unit-test
add_subdirectory(test)

# all exmaples
add_subdirectory(example)
