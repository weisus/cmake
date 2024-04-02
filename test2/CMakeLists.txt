cmake_minimum_required(VERSION 3.0)
project(test2)

# 搜索源文件
aux_source_directory(./ SRC)

# 添加头文件
include_directories(${HEADPATH})

# 链接静态库
link_directories(${LIBPATH})
link_libraries(${SORTLIB})

# 生成可执行文件
set(EXECUTABLE_OUTPUT_PATH ${EXEPATH})
add_executable(${APPNAME2} ${SRC})