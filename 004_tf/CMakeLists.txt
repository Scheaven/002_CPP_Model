#指定 cmake 的最小版本
cmake_minimum_required(VERSION 2.8.8)
 
#项目名称/工程名
project(demo)
 
#设置c++编译器
# Set C++14 as standard for the whole project
set(CMAKE_CXX_STANDARD 14)
 
#设置TENSORFLOW_DIR变量，变量内容为安装的tensorflow文件夹路径
set(TENSORFLOW_DIR /home/basic/workspace/Scheaven/s_opt/tensorflow-1.13.1)
 
# 将源码目录保存到变量中
aux_source_directory(./src DIR_SRCS)  # 搜索当前目录下的所有.cpp文件  
#add_library(demo ${SRC_LIST})   #明确指定包含哪些源文件                 
 
#设置包含的目录，项目中的include路径，换成自己的路径即可
include_directories( 
    ${CMAKE_CURRENT_SOURCE_DIR}
	/home/basic/workspace/Scheaven/s_opt/tensorflow-1.13.1
	/home/basic/workspace/Scheaven/s_opt/tensorflow-1.13.1/bazel-genfiles
	/home/basic/workspace/Scheaven/s_opt/tensorflow-1.13.1/bazel-bin/tensorflow
	/home/basic/workspace/Scheaven/s_opt/tensorflow-1.13.1/tensorflow/contrib/makefile/downloads/nsync/public
 	/home/basic/workspace/Scheaven/s_opt/tensorflow-1.13.1/tensorflow/contrib/makefile/downloads/eigen
   	/home/basic/workspace/Scheaven/s_opt/tensorflow-1.13.1/tensorflow/contrib/makefile/downloads/absl
   ) 
 
#设置链接库搜索目录，项目中lib路径
link_directories(${TENSORFLOW_DIR}/tensorflow/contrib/makefile/downloads/nsync/builds/default.linux.c++11)
link_directories(${TENSORFLOW_DIR}/home/basic/workspace/Scheaven/s_opt/tensorflow-1.13.1/bazel-bin/tensorflow)  #动态链接库目录/bazel-bin/tensorflow

link_directories(${TENSORFLOW_DIR}/tensorflow/contrib/makefile/gen/lib)
link_directories(${TENSORFLOW_DIR}/tensorflow/contrib/makefile/gen/protobuf-host/lib)
link_directories(${TENSORFLOW_DIR}/tensorflow/contrib/makefile/downloads/nsync/builds/default.linux.c++11)
link_directories(${TENSORFLOW_DIR}/bazel-bin/tensorflow)


#添加要编译的可执行文件
#add_executable(demo test.cpp)
add_executable(demo ${DIR_SRCS})    ## 生成可执行文件
 
#设置 target 需要链接的库
#添加可执行文件所需要的库,连接libtensorflow_cc.so和libtensorflow_framework库，链接动态链接库
#target_link_libraries(demo tensorflow_cc tensorflow_framework)
target_link_libraries(demo /home/basic/workspace/Scheaven/s_opt/tensorflow-1.13.1/bazel-bin/tensorflow/libtensorflow_cc.so /home/basic/workspace/Scheaven/s_opt/tensorflow-1.13.1/bazel-bin/tensorflow/libtensorflow_framework.so)