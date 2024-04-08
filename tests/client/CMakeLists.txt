cmake_minimum_required(VERSION 3.0)
project(client)

include_directories(${HEADPATH})

aux_source_directory(. SRC)

link_directories(${LIBPATH})
link_libraries(src)

set(EXECUTABLE_OUTPUT_PATH ${EXEPATH})
add_executable(client ${SRC})