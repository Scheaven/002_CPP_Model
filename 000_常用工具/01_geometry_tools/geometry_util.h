//
// Created by Scheaven on 2020/5/31.
//
#ifndef GEOMETRY_UTIL_H
#define GEOMETRY_UTIL_H

#include <vector>
#include <map>
#include <string>
#include <list>
#include <fstream>
#include <stdint.h>
#include "stdio.h"
#include <stdlib.h>
#include <math.h>

#include <iostream>
#include <cmath>
#include <cstring>
#include "assert.h"

/*** 常用常量 ***/
const double PI = 3.14159265;

typedef struct _Point
{
public:
    float x;
    float y;
    float z;

public:
    _Point(float x, float y);
    _Point();
    _Point(double a , double b , double c ); // 构造函数
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
#define MAX_POINT_POLYGON 64

struct Polygon {
    SPoint pt[MAX_POINT_POLYGON];
    int     n;

    Polygon(int n_ = 0 ) { assert(n_>= 0 && n_ < MAX_POINT_POLYGON); n = n_;}
    virtual ~Polygon() {}

    void clear() { n = 0; }
    void add(const SPoint &p) {if(n < MAX_POINT_POLYGON) pt[n++] = p;}
    void push_back(const SPoint &p) {add(p);}
    int size() const { return n;}
    SPoint getCenter() const ;
    const SPoint & operator[] (int index) const { assert(index >= 0 && index < n); return pt[index];}
    SPoint& operator[] (int index) { assert(index >= 0 && index < n); return pt[index]; }
    void pointsOrdered() ;
    float area() const ;
    bool pointIsInPolygon(SPoint p) const ;
};


void intersectPolygonSHPC(const Polygon * sub,const Polygon* clip,Polygon* res) ;
void intersectPolygonSHPC(const Polygon & sub,const Polygon& clip,Polygon& res) ;


//struct Point
//{
//    double x;    // x坐标
//    double y;    // y坐标
//    double z;    // z坐标（默认为0，如果需要三维点则给z赋值）
//
//    Point(double a , double b , double c = 0); // 构造函数
//    Point(); // 构造函数
//};

// 线,包括线段和直线
struct Line
{
    SPoint s;    // 起点
    SPoint e;    // 终点
    bool is_seg; // 是否是线段

    Line();    // 默认构造函数
    Line(SPoint a, SPoint b, bool _is_seg = true);    // 构造函数(默认是线段)
};

/** 多边形的点按照逆时针排序 start */
//若点a大于点b,即点a在点b顺时针方向,返回true,否则返回false
bool PointCmp(const SPoint &a,const SPoint &b,const SPoint &center);

SPoint ClockwiseSortPoints(std::vector<SPoint> &vPoints); // 多边形的点按照逆时针排序
/** 多边形的点按照逆时针排序 end */

// 点的加法
SPoint add(const SPoint& lhs, const SPoint& rhs);

// 点的减法
SPoint sub(const SPoint& lhs, const SPoint& rhs);

// 向量的乘法
SPoint mul(const SPoint& p, double ratio);

// 向量的除法
SPoint div(const SPoint& p, double ratio);

// 点判断相等
bool equal(const SPoint& lhs, const SPoint& rhs);

// 1.2、矢量的长度
//
// 参数： vec 矢量
//
double length(const SPoint& vec);

// 1.3、矢量标准化（矢量的长度规约到1）
//
// 参数： vec ： 矢量
//
SPoint normalize(const SPoint& vec);

// 1.4、矢量点乘
//
// 参数：(p1-op)为矢量1，（p2-op）为矢量2
//
double dotMultiply(const SPoint& op, const SPoint& p1, const SPoint& p2);

// 参数：vec1为矢量1，vec2为矢量2
//
double dotMultiply(const SPoint& vec1, const SPoint& vec2);

// 1.5、矢量叉乘
//
// 参数：(p1-op)为矢量1，（p2-op）为矢量2
//
SPoint multiply(const SPoint& op, const SPoint& p1, const SPoint& p2);

// 参数： vec1为矢量1，vec2为矢量2
//
SPoint multiply(const SPoint& vec1, const SPoint& vec2);

// 1.9、点是否在线上
// 线分为直线和线段，直线表示的是直线是否经过点
//
// 参数：p : 点  l : 线段或者线
//
bool isponl(const SPoint& p, const Line& l);

// 1.11、矢量夹角余弦
//

// 参数： vec1 矢量1  vec2 矢量2
//
double Cos(const SPoint& vec1, const SPoint& vec2);

// 参数： op : 矢量公共点 p1 : 矢量1端点 p2 : 矢量2端点
//
double Cos(const SPoint& op, const SPoint& p1, const SPoint& p2);

bool isSegIntersect(const Line& l1, const Line& l2, SPoint& inter_p);

#endif //GEOMETRY_UTIL_H
