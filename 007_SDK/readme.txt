01_Implicit_call C++ 接口的隐式调用，统一函数调用形式


封装SDK接口的关键字是SHARED
CMakeLists_SHARED是SDK封装的CMakeList.txt样例
文件中 执行文件不要，需要添加cuda_add_library(${PROJECT_NAME} SHARED ${sources} ${CURRENT_HEADERS})包