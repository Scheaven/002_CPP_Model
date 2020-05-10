//
// Created by Scheaven on 2020/4/26.
//

#ifndef INC_01_CPP_SORT_STD_TARGET_H
#define INC_01_CPP_SORT_STD_TARGET_H

#include <stdint.h>

typedef struct _TImage{
    // Image (BGR), data
    unsigned char *data;
    // Image width
    int width;
    // Image height
    int height;
    // Image channel
    int channel;
}TImage;

typedef struct _TRect{
    int left;
    int top;
    int right;
    int bottom;
}TRect;

// 获取sdk运行结果, 单个的结果元素,如一张图片内检测到多个目标,每个目标是一个Target
typedef struct _Target{
    // target id 追踪
    uint64_t        id;
    // 检测置信度
    int             confidence;
    // target位置坐标
    TRect           rect;
    // sdk类型,如人脸等
    char            type[64];
    // target提取的特征值
    char*           feature;
    // target的一些属性, 如年龄,种族,颜色等
    char*           attribute;
}Target;

// 本次运行sdk的结果汇总, 是最后要传出的结构体
typedef struct _TResult{
    Target *targets;
    int count;
}TResult;



#endif //INC_01_CPP_SORT_STD_TARGET_H
