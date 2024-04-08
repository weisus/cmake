cmake_minimum_required(VERSION 3.0)
project(cmake)

# 静态库生成路径
set(LIBPATH ${PROJECT_SOURCE_DIR}/lib)

# 可执行文件的存储目录
set(EXEPATH ${PROJECT_SOURCE_DIR}/bin)

# 设置头文件目录
set(HEADPATH ${PROJECT_SOURCE_DIR}/include)

# 添加子目录
add_subdirectory(src)
add_subdirectory(tests)