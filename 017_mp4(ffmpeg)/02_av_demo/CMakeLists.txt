cmake_minimum_required(VERSION 3.5)

#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS}  -fvisibility=hidden -DEIGEN_MAX_ALIGN_BYTES=32 -DEIGEN_DONT_VECTORIZE -march=native -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}   -fvisibility=hidden -DEIGEN_MAX_ALIGN_BYTES=32 -DEIGEN_DONT_VECTORIZE -fPIC -march=native -DGPU -DCUDNN -DOPENCV -g -std=c++11  -W -O3 -pthread -Wl,--no-as-needed  -DS_DEBUG")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}   -fvisibility=hidden -DEIGEN_MAX_ALIGN_BYTES=32 -DEIGEN_DONT_VECTORIZE -fPIC -march=native -DGPU -DCUDNN -DOPENCV -g -std=c++11 -W -O3 -pthread -Wl,--no-as-needed")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -fvisibility=hidden -DGPU -DCUDNN -DOPENCV -g -std=c++14 -fPIC -W -O3 -Wl,--no-as-needed")  # 编译C脚本时调用GPU环境信息
#set(CMAKE_C_FLAGS "-fvisibility=hidden")
#set(CMAKE_CXX_FLAGS "-fvisibility=hidden")

project(util)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE CURRENT_HEADERS
            src/*.h
        )

# 检索查找文件信息
file(GLOB sources
         src/*.cpp
        )

source_group("Include" FILES ${CURRENT_HEADERS})
source_group("Source" FILES ${sources})

# set(OPENCV_DIR /opt/toolkits/opencv)
# include_directories(${OPENCV_DIR}/include/opencv4)
# link_directories(${OPENCV_DIR}/lib)

set(OpenCV_DIR /data/disk2/opt/01_opencv/opencv4.5.1/build)
FIND_PACKAGE(OpenCV REQUIRED)

SET(LIBS
        opencv_core
        opencv_highgui
        opencv_imgcodecs
        opencv_imgproc
        opencv_videoio
        opencv_video
        opencv_features2d
        opencv_flann
        opencv_calib3d
        avcodec
        avformat
        avfilter
        avutil
        swscale
        swresample
        avutil
        )

include_directories(/usr/include/x86_64-linux-gnu/)
include_directories("src")

link_directories(/usr/lib/x86_64-linux-gnu/)
link_directories(/usr/local/lib/)
link_directories(/usr/local/cuda-10.0/lib64)  #动态链接库目录/bazel-bin/tensorflow

add_executable(${PROJECT_NAME} ${sources} ${CURRENT_HEADERS})
target_link_libraries(${PROJECT_NAME} ${LIBS})
