cmake_minimum_required(VERSION 3.5)
project(yolo)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/./build)
set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_BUILD_TYPE debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGPU -DCUDNN  -pthread")

add_compile_options(-fPIC -g -Wall  -Wshadow -Wno-sign-compare -w)
#add_definitions(-DDEBUG_ERR -DDEBUG_INFO)
#add_definitions(-DDEBUG)

set(TENSORFLOW_DIR /home/basic/test/tensorflow-1.14.0)

SET(SOURCES
	
        )

link_directories(
	${TENSORFLOW_DIR}/tensorflow/contrib/makefile/downloads/nsync/builds/default.linux.c++11
	${TENSORFLOW_DIR}/bazel-bin/tensorflow
	#/usr/local/lib
	/usr/local/cuda-10.0/lib64
	/usr/lib/x86_64-linux-gnu/

    #		${CMAKE_SOURCE_DIR}/opencv3.4.8/lib
	/home/basic/Scheaven/02_SDK/opencv2.4.13/lib
    ./
)

#find_library(yolo NAMES yolo_tracking PATHS ${CMAKE_SOURCE_DIR}/yoloTrackBasic/)
#message(${yolo})

SET(LIBS
	yolo_tracking
#opencv_videoio
	opencv_core
        opencv_highgui
       opencv_imgproc
        opencv_video
        tensorflow_cc
        tensorflow_framework
        cudart
        cublas
	stdc++fs  #设置-lstdc++fs 新链接器选项，防止std等gcc库调用不到
        curand
        cuda
        cudnn
		dl
		m
        )

include_directories(
#/usr/include/eigen3/
#	/usr/local/tensorflow-1.14.0    
#   /usr/local/tensorflow-1.14.0/bazel-genfiles
#   /usr/local/tensorflow-1.14.0/bazel-bin/tensorflow
#  /usr/local/tensorflow-1.14.0/tensorflow/contrib/makefile/downloads/     nsync/public
#  /usr/local/tensorflow-1.14.0/tensorflow/contrib/makefile/downloads/     eigen
#  /usr/local/tensorflow-1.14.0/tensorflow/contrib/makefile/downloads/     absl
#/usr/local/tensorflow-1.14.0/tensorflow/contrib/makefile/downloads/     protobuf/src
                #/usr/include/
  ./yoloTrackBasic/
  /home/basic/Scheaven/02_SDK/opencv2.4.13/include
  ./
)

#foreach(src in ${LIBS})
#message(${src})
#endforeach()

add_executable(${PROJECT_NAME}
		sdk.cpp
        main.cpp
        ${SOURCES}
        )

target_link_libraries(${PROJECT_NAME}
        ${LIBS}
        )
