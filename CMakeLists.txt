# version needed
cmake_minimum_required (VERSION 2.8)
# fix the compile-problem in mac-osx
set(CMAKE_MACOSX_RPATH 1)

# project declare
project(isee)

# all depends 
add_subdirectory(depends)

# all librarys
add_subdirectory(code)

# all unit-test
add_subdirectory(test)

# all exmaples
add_subdirectory(example)
