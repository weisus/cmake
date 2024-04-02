cmake_minimum_required(VERSION 3.0)
project(test)

# 静态库生成路径
set(LIBPATH ${PROJECT_SOURCE_DIR}/lib)

# 可执行文件的存储目录
set(EXEPATH ${PROJECT_SOURCE_DIR}/bin)

# 设置头文件目录
set(HEADPATH ${PROJECT_SOURCE_DIR}/include)

# 库文件的名字
set(CALCLIB calc)
set(SORTLIB sort)

# 可执行文件的名字
set(APPNAME1 app1)
set(APPNAME2 app2)

# 添加子目录
add_subdirectory(calc)
add_subdirectory(sort)
add_subdirectory(test1)
add_subdirectory(test2)