cmake_minimum_required(VERSION 3.0)
project(sort)

# 搜索源文件
aux_source_directory(./ SRC)

# 添加头文件
include_directories(${HEADPATH})

# 生成静态库
set(LIBRARY_OUTPUT_PATH ${LIBPATH})
add_library(${SORTLIB} STATIC ${SRC})