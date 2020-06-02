//
// Created by Scheaven on 2020/5/31.
//
#ifndef INC_01_DARKNET_SORT_GEOMETRY_UTIL_H
#define INC_01_DARKNET_SORT_GEOMETRY_UTIL_H

#include <stdlib.h>
#include <math.h>


typedef struct _Point
{
public:
    float x;
    float y;

public:
    _Point(float x, float y);
    _Point();

} SPoint;

// 多边形区域结构
typedef struct _PInfo
{
    SPoint2f* point;
    int count;
}RegInfo;

float calDistance(SPoint A, SPoint B);


//作用：判断点是否在多边形内
//p指目标点， ptPolygon指多边形的点集合， nCount指多边形的边数
bool Pt_in_Polygon(SPoint point, RegInfo* polygon);

#endif //INC_01_DARKNET_SORT_GEOMETRY_UTIL_H
