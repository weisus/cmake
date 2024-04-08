cmake_minimum_required(VERSION 3.0)
project(server)

include_directories(${HEADPATH})

aux_source_directory(. SRC)

link_directories(${LIBPATH})
link_libraries(pthread src)

set(EXECUTABLE_OUTPUT_PATH ${EXEPATH})
add_executable(server ${SRC})