//
// Created by Scheaven on 2020/4/20.
//

#ifndef INC_01_CPP_SORT_RESULT_UTIL_H
#define INC_01_CPP_SORT_RESULT_UTIL_H
#include "../config.h"
#include "../encoder_tools/model.h"

// 返回结果的结构体
struct RESULT_STRUCT
{
public:
    int human_id;
    float confidence;
    cv::Rect rect;
};

typedef std::vector<RESULT_STRUCT> FRAME_RESULT; // 返回一张画面中的结果信息

// ---SDK----.

// 结果传递过来待检测数据的形式
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
    int           feature_size;
    // target的一些属性, 如年龄,种族,颜色等
    char*           attribute;
    int           attribute_size;
}Target;


// 本次运行sdk的结果汇总, 是最后要传出的结构体
typedef struct _TResult{
    Target *targets;
    int count;
}TResult;

void switch_result(DETECTIONS& detections, FRAME_RESULT& results_vec); // 实现detection到result的结果化转换
float cul_overlap_area(int Ax, int Ay, int Bx, int By, int Cx, int Cy, int Dx, int Dy); //计算两个框的重叠率



#endif //INC_01_CPP_SORT_UTIL_H
