//
// Created by Scheaven on 2020/5/20.
//

#ifndef INC_01_COORDINATE_TRANSFORMATION_CON_TARGET_H
#define INC_01_COORDINATE_TRANSFORMATION_CON_TARGET_H

#include <vector>
#include <map>
#include <string>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

#include <stdint.h>

// 初始化时区域结构
typedef struct _PInfo
{
    cv::Point2f* point;
    int count;
}RegInfo;

typedef struct _CamVec
{
    RegInfo *regInfo;
}CamVec;


// 传输的人体站立的点位信息
typedef struct _HumanInfo
{
    int human_id;
    cv::Point2f point;
//    float * feature;
}HumanInfo;

typedef struct _MatchHuman
{
    HumanInfo* humanInfo;
    int count;      //一共多少个人的坐标点
}MatchHuman;





// 获取最终的结果信息
typedef struct _TsimRTL
{
    float confidence;
}TsimRTL;

typedef struct _Target
{
    TsimRTL *tsimRtl;
}Target;

typedef std::vector<Target> FIRST_VEC;


#endif //INC_01_COORDINATE_TRANSFORMATION_CON_TARGET_H
