//
// Created by Scheaven on 2020/5/31.
//

#include "geometry_util.h"

SPoint::_Point() {}
SPoint::_Point(float x, float y)
{
    this->x = x;
    this->y = y;
}

float calDistance(SPoint A, SPoint B)
{
    float x_d, y_d;
    x_d = A.x - B.x;
    y_d = A.y - B.y;
    float len = sqrt(x_d * x_d + y_d * y_d);
    return len;
}

/*
如果从点P作水平向左的射线的话，假设P在多边形内部，那么这条射线与多边形的交点必为奇数，如果P在多边形外部，则交点个数必为偶数（0也在内）。所以，我们可以顺序（顺时针或逆时针）考虑多边形的每条边，求出交点的总个数。还有一些特殊情况要考虑。假如考虑边(P1,P2)，
1) 如果射线正好穿过P1或者P2,那么这个交点会被算作2次，处理办法是如果P的从坐标与P1,P2中较小的纵坐标相同，则直接忽略这种情况
2) 如果射线水平，则射线要么与其无交点，要么有无数个，这种情况也直接忽略。
3) 如果射线竖直，而P的横坐标小于P1,P2的横坐标，则必然相交。
4) 再判断相交之前，先判断P是否在边(P1,P2)的上面，如果在，则直接得出结论：P再多边形内部。
 * */
bool Pt_in_Polygon(SPoint point, RegInfo* polygon)
{
    int nCross = 0;
    for (int i = 0; i < polygon->count; ++i)
    {
        SPoint p1 = polygon[i];
        SPoint p2 = polygon[(i+1)%polygon->count];

        if ( p1.y == p2.y )
            continue;
        if ( p.y < min(p1.y, p2.y) )
            continue;
        if ( p.y >= max(p1.y, p2.y) )
            continue;

        // 求交点的x坐标（由直线两点式方程转化而来）
        float x = (float)(p.y - p1.y) * (float)(p2.x - p1.x) / (float)(p2.y - p1.y) + p1.x;

        // 只统计p1p2与p向右射线的交点
        if ( x > p.x )
        {
            nCross++;
        }

    }

    // 交点为偶数，点在多边形之外
    // 交点为奇数，点在多边形之内
    if ((nCross % 2) == 1)
    {
        return true; //在内部
    }
    else
    {
        return false; //在外部
    }

}