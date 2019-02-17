cmake_minimum_required(VERSION 3.13)

set(DEFAULT_FLAGS "-Wall -Wextra -pedantic -pedantic-errors -Wno-vla-extension -Wno-missing-braces -Wno-gnu-anonymous-struct -Wno-nested-anon-types -march=native -Werror")
set(UNUSED_FLAGS "-Wno-unused-function -Wno-unused-variable -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${DEFAULT_FLAGS} ${UNUSED_FLAGS} -g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${DEFAULT_FLAGS} ${UNUSED_FLAGS} -O2")

project(ProjectEuler)
add_subdirectory(src)
