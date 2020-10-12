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
    float len = sqrt(x_d * x_d + 4*y_d * y_d);
    return len;
}

/*
如果从点P作水平向左的射线的话，假设P在多边形内部，那么这条射线与多边形的交点必为奇数，如果P在多边形外部，则交点个数必为偶数（0也在内）。所以，我们可以顺序（顺时针或逆时针）考虑多边形的每条边，求出交点的总个数。还有一些特殊情况要考虑。假如考虑边(P1,P2)，
1) 如果射线正好穿过P1或者P2,那么这个交点会被算作2次，处理办法是如果P的从坐标与P1,P2中较小的纵坐标相同，则直接忽略这种情况
2) 如果射线水平，则射线要么与其无交点，要么有无数个，这种情况也直接忽略。
3) 如果射线竖直，而P的横坐标小于P1,P2的横坐标，则必然相交。
4) 再判断相交之前，先判断P是否在边(P1,P2)的上面，如果在，则直接得出结论：P再多边形内部。
 * */
//bool Pt_in_Polygon(SPoint point, RegInfo* polygon)
//{
//    int nCross = 0;
//    for (int i = 0; i < polygon->count; ++i)
//    {
//        SPoint p1 = polygon[i];
//        SPoint p2 = polygon[(i+1)%polygon->count];
//
//        if ( p1.y == p2.y )
//            continue;
//        if ( p.y < min(p1.y, p2.y) )
//            continue;
//        if ( p.y >= max(p1.y, p2.y) )
//            continue;
//
//        // 求交点的x坐标（由直线两点式方程转化而来）
//        float x = (float)(p.y - p1.y) * (float)(p2.x - p1.x) / (float)(p2.y - p1.y) + p1.x;
//
//        // 只统计p1p2与p向右射线的交点
//        if ( x > p.x )
//        {
//            nCross++;
//        }
//
//    }
//
//    // 交点为偶数，点在多边形之外
//    // 交点为奇数，点在多边形之内
//    if ((nCross % 2) == 1)
//    {
//        return true; //在内部
//    }
//    else
//    {
//        return false; //在外部
//    }

//}


/*
 * 多边形部分，判断多边形重叠率的计算
 */

//float computeArea(const SPoint * pt,int n ) {
//    float area0 = 0.f;
//    for (int i = 0 ; i < n ; i++ )
//    {
//        int j = (i+1)%n;
//        area0 += pt[i].x * pt[j].y;
//        area0 -= pt[i].y * pt[j].x;
//    }
//    return 0.5f * fabs(area0);
//}
//
//struct PointAngle{
//    SPoint p;
//    float angle;
//};
//
//float Polygon::area() const {
//    return computeArea(pt,n);
//}
//
//static inline int cross(const SPoint* a,const SPoint* b) {
//    return a->x * b->y - a->y * b->x;
//}
//
//static inline SPoint* vsub(const SPoint* a,const SPoint* b, SPoint* res) {
//    res->x = a->x - b->x;
//    res->y = a->y - b->y;
//    return res;
//}
//
//
//static int line_sect(const SPoint* x0,const SPoint* x1,const SPoint* y0,const SPoint* y1, SPoint* res) {
//    SPoint dx, dy, d;
//    vsub(x1, x0, &dx);
//    vsub(y1, y0, &dy);
//    vsub(x0, y0, &d);
//    float dyx = (float)cross(&dy, &dx);
//    if (!dyx) return 0;
//    dyx = cross(&d, &dx) / dyx;
//    if (dyx <= 0 || dyx >= 1) return 0;
//    res->x = int(y0->x + dyx * dy.x);
//    res->y = int(y0->y + dyx * dy.y);
//    return 1;
//}
//
//static int left_of(const SPoint* a,const SPoint* b,const SPoint* c) {
//    SPoint tmp1, tmp2;
//    int x;
//    vsub(b, a, &tmp1);
//    vsub(c, b, &tmp2);
//    x = cross(&tmp1, &tmp2);
//    return x < 0 ? -1 : x > 0;
//}
//
//static void poly_edge_clip(const Polygon* sub,const  SPoint* x0,const  SPoint* x1, int left, Polygon* res) {
//    int i, side0, side1;
//    SPoint tmp;
//    const SPoint* v0 = sub->pt+ sub->n - 1;
//    const SPoint* v1;
//    res->clear();
//
//    side0 = left_of(x0, x1, v0);
//    if (side0 != -left) res->add(*v0);
//
//    for (i = 0; i < sub->n; i++) {
//        v1 = sub->pt + i;
//        side1 = left_of(x0, x1, v1);
//        if (side0 + side1 == 0 && side0)
//            /* last point and current straddle the edge */
//            if (line_sect(x0, x1, v0, v1, &tmp))
//                res->add(tmp);
//        if (i == sub->n - 1) break;
//        if (side1 != -left) res->add(*v1);
//        v0 = v1;
//        side0 = side1;
//    }
//}
//
//static int poly_winding(const Polygon* p) {
//    return left_of(p->pt, p->pt + 1, p->pt + 2);
//}
//
//
//void intersectPolygonSHPC(const Polygon * sub, const Polygon* clip, Polygon* res)
//{
//    int i;
//    Polygon P1,P2;
//    Polygon *p1 = &P1;
//    Polygon *p2 = &P2;
//    Polygon *tmp;
//
//    int dir = poly_winding(clip);
//    poly_edge_clip(sub, clip->pt + clip->n - 1, clip->pt, dir, p2);
//    for (i = 0; i < clip->n - 1; i++) {
//        tmp = p2; p2 = p1; p1 = tmp;
//        if(p1->n == 0) {
//            p2->n = 0;
//            break;
//        }
//        poly_edge_clip(p1, clip->pt + i, clip->pt + i + 1, dir, p2);
//    }
//    res->clear();
//    for (i = 0 ; i < p2->n ; i++) res->add(p2->pt[i]);
//}
//
//void intersectPolygonSHPC(const Polygon & sub,const Polygon& clip,Polygon& res) {
//    intersectPolygonSHPC(&sub,&clip,&res);
//}
//

