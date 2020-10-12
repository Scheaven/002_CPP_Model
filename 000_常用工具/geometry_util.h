//
// Created by Scheaven on 2020/5/31.
//
#ifndef GEOMETRY_UTIL_H
#define GEOMETRY_UTIL_H

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <cmath>
#include <cstring>
#include "assert.h"
using namespace std;

typedef struct _Point
{
public:
    float x;
    float y;

public:
    _Point(float x, float y);
    _Point();
}SPoint;

// 多边形区域结构
typedef struct _PInfo
{
    SPoint* point;
    int count;
}RegInfo;

float calDistance(SPoint A, SPoint B);


//作用：判断点是否在多边形内
//p指目标点， ptPolygon指多边形的点集合， nCount指多边形的边数
bool Pt_in_Polygon(SPoint point, RegInfo* polygon);



/*
 * 多边形部分，判断多边形重叠率的计算
 */
//#define MAX_POINT_POLYGON 64
//
//struct Polygon {
//    SPoint pt[MAX_POINT_POLYGON];
//    int     n;
//
//    Polygon(int n_ = 0 ) { assert(n_>= 0 && n_ < MAX_POINT_POLYGON); n = n_;}
//    virtual ~Polygon() {}
//
//    void clear() { n = 0; }
//    void add(const SPoint &p) {if(n < MAX_POINT_POLYGON) pt[n++] = p;}
//    void push_back(const SPoint &p) {add(p);}
//    int size() const { return n;}
//    SPoint getCenter() const ;
//    const SPoint & operator[] (int index) const { assert(index >= 0 && index < n); return pt[index];}
//    SPoint& operator[] (int index) { assert(index >= 0 && index < n); return pt[index]; }
//    void pointsOrdered() ;
//    float area() const ;
//    bool pointIsInPolygon(SPoint p) const ;
//};
//
//
//void intersectPolygonSHPC(const Polygon * sub,const Polygon* clip,Polygon* res) ;
//void intersectPolygonSHPC(const Polygon & sub,const Polygon& clip,Polygon& res) ;

#endif //INC_01_DARKNET_SORT_GEOMETRY_UTIL_H
