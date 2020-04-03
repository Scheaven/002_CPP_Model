cmake_minimum_required(VERSION 3.5)

#项目名称/工程名
project(track)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
#设置c++编译器

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_BUILD_TYPE debug)
add_compile_options(-fPIC -g -Wall -Wshadow -Wno-sign-compare -w)
#add_definitions(-DDEBUG_ERR -DDEBUG_INFO)
#add_definitions(-DDEBUG)

#设置变量，变量内容为文件夹路径（添加TensorFlow的路径，同样可以设置）
SET(SOURCES
#        ./lib/core/detecter_manager.cpp
#        ./lib/core/tracker_manager.cpp
#        ./lib/detecter_tools/FeatureTensor.cpp
#        ./lib/detecter_tools/model.cpp
#        ./lib/Munkres_assign/hungarianoper.cpp
#        ./lib/Munkres_assign/munkres/munkres.cpp
#        ./lib/tracker_tools/kalmanfilter.cpp
#        ./lib/tracker_tools/linear_assignment.cpp
#        ./lib/tracker_tools/nn_matching.cpp
#        ./lib/tracker_tools/track.cpp
#        ./lib/tracker_tools/tracker.cpp
#        ./lib/utils/t_utils.cpp
        )
SET(LIBS
        opencv_core
        opencv_highgui
        opencv_imgcodecs
        opencv_imgproc
        opencv_videoio
        opencv_video
        #tensorflow_cc
        #tensorflow_framework
        )
        
#设置包含的目录，项目中的include路径，换成自己的路径即可
include_directories(
        /home/disk1/s_opt/opencv/include/opencv4
        ./
#        ./lib/core
#        ./lib/detecter_tools
#        ./lib/Munkres_assign
#        ./lib/utils
#        ./lib/Munkres_assign/munkres
#       /usr/local/include/tf
#       ../tensorflow/bazel-genfiles
#       ../tensorflow/tensorflow
#       ../tensorflow/third_party
#       ../tensorflow/bazel-tensorflow/external/eigen_archive
#        /usr/include/eigen3
#        /usr/local/lib/python3.7/site-packages/tensorflow/include/
)
#include_directories(".")
#include_directories("./lib/core")
#include_directories("./lib/detecter_tools")
#include_directories("./lib/Munkres_assign")
#include_directories("./lib/tracker_tools")
#include_directories("./lib/utils")
#include_directories("./lib/Munkres_assign/munkres")

#设置链接库搜索目录，项目中lib路径
link_directories(
        /usr/local/lib
        /home/disk1/s_opt/opencv/lib  # 添加opencv的lib
#        ../tensorflow/bazel-bin/tensorflow
)

#添加要编译的可执行文件
add_executable(${PROJECT_NAME}
        main.cpp
        ${SOURCES}
        )

#设置 target 需要链接的库
#添加可执行文件所需要的库,连接libtensorflow_cc.so和libtensorflow_framework库，链接动态链接库
target_link_libraries(${PROJECT_NAME}
        ${LIBS}
        )