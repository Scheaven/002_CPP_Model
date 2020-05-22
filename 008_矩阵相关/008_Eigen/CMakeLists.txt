cmake_minimum_required(VERSION 3.5)
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -DEIGEN_MAX_ALIGN_BYTES=32 -DEIGEN_DONT_VECTORIZE -march=native -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}   -DEIGEN_MAX_ALIGN_BYTES=32 -DEIGEN_DONT_VECTORIZE -march=native -DGPU -DCUDNN -DOPENCV -g -std=c++11 -W -pthread")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS}     -DEIGEN_MAX_ALIGN_BYTES=32 -DEIGEN_DONT_VECTORIZE -march=native -DGPU -DCUDNN -DOPENCV -g -std=c++11 -W  -pthread")

#项目名称/工程名
project(demo)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
#设置c++编译器

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_BUILD_TYPE debug)
add_compile_options(-fPIC -g -Wall -Wshadow -Wno-sign-compare -w)
#add_definitions(-DDEBUG_ERR -DDEBUG_INFO)
#add_definitions(-DDEBUG)
#add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)


file(GLOB_RECURSE CURRENT_HEADERS
  ./*.h
  ./lib/*.h
  ./lib/core/*.h
  ./lib/tracker_tools/*.h
  ./lib/encoder_tools/*.h
  ./lib/detecter_tools/*.h
  ./lib/detecter_tools/extra/*.h
  ./lib/Munkres_assign/*.h
  ./lib/utils/*.h
  ./lib/detecter_tools/*.hpp
  ./lib/detecter_tools/*.cuh
  ./lib/detecter_tools/darknet/*.hpp
  ./lib/detecter_tools/darknet/*.cuh)

# 检索查找文件信息
file(GLOB sources
./*.cpp
./lib/*.cpp
./lib/core/*.cpp
./lib/tracker_tools/*.cpp
./lib/encoder_tools/*.cpp
./lib/detecter_tools/*.cpp
./lib/Munkres_assign/*.cpp
./lib/utils/*.cpp
./lib/detecter_tools/*.cpp
./lib/detecter_tools/darknet/*.c
./lib/detecter_tools/darknet/*.cpp
./lib/detecter_tools/darknet/*.cu)


#foreach(s range ${sources})
#message(${s})
#endforeach()


source_group("Include" FILES ${CURRENT_HEADERS}) 
source_group("Source" FILES ${sources}) 


#cudaS
find_package(CUDA REQUIRED)

message("-- CUDA version:$(CUDA_VERSION)")

# 设置环境的模型查找，如果CUDA版本大于9,则执行CUDA环境的模型查找
if(CUDA_VERSION_MAJOR GREATER 9)
        message("-- CUDA ${CUDA_VERSION_MAJOR} detected")
        set(
                CUDA_NVCC_FLAGS
                ${CUDA_NVCC_FLAGS}; 
                -gencode arch=compute_61,code=sm_61 # 不同GPU有不同的算力指数，可查看算力表
        )
        set(CUDA_NVCC_FLAGS_RELWITHDEBINFO "--device-debug;-lineinfo")
#find_package(OpenCV REQUIRED) # 查找系统的默认opencv环境
#message(${OpenCV_LIBS})
endif()


#设置TENSORFLOW_DIR变量，变量内容为安装的tensorflow文件夹路径
set(TENSORFLOW_DIR /home/disk1/s_opt/tensorflow/tensorflow-1.14.0)

link_directories(/usr/local/cuda-10.0/lib64)
#link_directories(/usr/local/lib)

SET(LIBS
        opencv_core
        opencv_highgui
        opencv_imgcodecs
        opencv_imgproc
        opencv_videoio
        opencv_video
        tensorflow_cc
        tensorflow_framework   
        cudart
        cublas     
	    stdc++fs  #设置-lstdc++fs 新链接器选项，防止std等gcc库调用不到
        curand
        cuda
        cudnn
        )

# 将源码目录保存到变量中
#aux_source_directory(./src DIR_SRCS)  # 搜索当前目录下的所有.cpp文件  
#add_library(demo ${SRC_LIST})   #明确指定包含哪些源文件 


#设置包含的目录，项目中的include路径，换成自己的路径即可
include_directories(        
        ${CMAKE_CURRENT_SOURCE_DIR}
        /home/disk1/s_opt/tensorflow/tensorflow-1.14.0
        /home/disk1/s_opt/tensorflow/tensorflow-1.14.0/bazel-genfiles
        /home/disk1/s_opt/tensorflow/tensorflow-1.14.0/bazel-bin/tensorflow
        /home/disk1/s_opt/tensorflow/tensorflow-1.14.0/tensorflow/contrib/makefile/downloads/nsync/public
        /home/disk1/s_opt/tensorflow/tensorflow-1.14.0/tensorflow/contrib/makefile/downloads/eigen
        /home/disk1/s_opt/tensorflow/tensorflow-1.14.0/tensorflow/contrib/makefile/downloads/absl
        /home/disk1/s_opt/tensorflow/tensorflow-1.14.0/tensorflow/contrib/makefile/downloads/protobuf/src
)
include_directories(/home/disk1/s_opt/opencv/opencv3.4.8/include) # 使用了系统的opencv，所以就不用这个了
include_directories(/usr/local/cuda/include)
include_directories(".")
include_directories("./lib")
include_directories("./lib/core")
include_directories("./lib/detecter_tools")
include_directories("./lib/encoder_tools")
include_directories("./lib/Munkres_assign")
include_directories("./lib/tracker_tools")
include_directories("./lib/utils")
include_directories("./lib/Munkres_assign/munkres")
#include_directories("/usr/include")


#设置链接库搜索目录，项目中lib路径
link_directories(${TENSORFLOW_DIR}/tensorflow/contrib/makefile/downloads/nsync/builds/default.linux.c++11)
link_directories(${TENSORFLOW_DIR}/bazel-bin/tensorflow)  #动态链接库目录/bazel-bin/tensorflow
#link_directories(/usr/local/lib)
link_directories(/usr/local/cuda/lib64)  #动态链接库目录/bazel-bin/tensorflow
link_directories(/home/disk1/s_opt/opencv/opencv3.4.8/lib)  #动态链接库目录/bazel-bin/tensorflow
#link_directories("/usr/lib/x86_64-linux-gnu")


#添加要编译的可执行文件
cuda_add_executable(${PROJECT_NAME}
	SDK_main.cpp
        ${sources}
        ${CURRENT_HEADERS}
        )
#add_executable(demo ${DIR_SRCS})    ## 生成可执行文件


#设置 target 需要链接的库
#添加可执行文件所需要的库,连接libtensorflow_cc.so和libtensorflow_framework库，链接动态链接库
target_link_libraries(${PROJECT_NAME}
	${LIBS}
        )
