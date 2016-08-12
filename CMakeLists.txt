# version needed
cmake_minimum_required (VERSION 2.8)
# c89
set(CMAKE_C_FLAGS "-O2 -Wall -Werror=declaration-after-statement -std=c89 -pedantic -Dinline='' -Wno-c99-extensions -Wno-variadic-macros -Wno-unused-function")

# project declare
project(isee)

# target: isee-run
add_executable(isee-run main.c)

