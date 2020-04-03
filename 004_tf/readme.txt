1、安装TensorFlow需要对应的bazel版本
2、必须安装到用户所在的盘
3、配置细则具体查看云笔记
4、安装命令：

#编译C++ API，生成.so文件，Tensorflow调用CUDA

bazel build --config=opt --config=cuda //tensorflow:libtensorflow_cc.so
bazel build --config=opt --config=cuda_clang //tensorflow:libtensorflow_cc.so
报错用--config=cuda_clang代替 --config=cuda

#编译C++ API，生成.so文件，Tensorflow不调用CUDA

bazel build --config=opt //tensorflow:libtensorflow_cc.so