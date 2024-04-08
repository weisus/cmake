cmake_minimum_required(VERSION 3.0)
project(src)

include_directories(${HEADPATH})

aux_source_directory(. SRC)

set(LIBRARY_OUTPUT_PATH ${LIBPATH})
add_library(src STATIC ${SRC})