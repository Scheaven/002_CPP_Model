//
// Created by Scheaven on 2020/4/26.
//

#include "h_interface.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdint.h>
#include <vector>
using std::__cxx11::list;//I am forced to use std-c++11 because of wxWidgets 3.0.2
#include <cstdlib>


class T
{
public:
	T();
	~T();
	void single_SDK( const int cam_id, const void *frame,TResult *t_result);;
};

T::single_SDK(const int cam_id, const void *img, TResult *t_result)
{
    cout << "返回结果" << endl;
}


// 创建句柄
YOLOTRACK_API void* create(const char *conf, int *max_chan)
{
    T *handle = new T();
    return handle;
}


//释放句柄
YOLOTRACK_API void release(void* handle)
{
    TrackerManager *h = (TrackerManager*)handle;
    delete h;
    h = NULL;
    cout << "release success" << endl;
}

//获取结果
YOLOTRACK_API void* get_result(void *handle, const void *img, const int chan){
    TrackerManager * h = (TrackerManager*)handle;
//    TResult *t_result = new TResult();
    TResult *t_result = (TResult*)malloc(sizeof(TResult));
    init_TResult(t_result);
    h->single_SDK(chan, img, t_result);

    return t_result;
}


//释放结果结构
YOLOTRACK_API void release_result(void *res)
{
    if (!res) return;

    TResult *cres = (TResult*)res;

//    delete cres;

    for (int i = 0; i < cres->count; i++){
        Target t = cres->targets[i];
        if (t.feature) free(t.feature);
        if (t.attribute) free(t.attribute);
    }

    free(cres->targets);
    free(cres);
};



void init_TResult(TResult *t){
    t->count = 0;
    t->targets = nullptr;
}