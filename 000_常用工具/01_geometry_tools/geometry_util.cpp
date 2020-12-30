//
// Created by Scheaven on 2020/5/31.
//

#include "geometry_util.h"
using namespace std;


SPoint::_Point() {}
SPoint::_Point(float x, float y)
{
    this->x = x;
    this->y = y;
    this->z = 0;
}

SPoint::_Point(double a, double b, double c)
{
   x = a; y = b; z = c;
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

float computeArea(const SPoint * pt,int n ) {
    float area0 = 0.f;
    for (int i = 0 ; i < n ; i++ )
    {
        int j = (i+1)%n;
        area0 += pt[i].x * pt[j].y;
        area0 -= pt[i].y * pt[j].x;
    }
    return 0.5f * fabs(area0);
}

struct PointAngle{
    SPoint p;
    float angle;
};

float Polygon::area() const {
    return computeArea(pt,n);
}

static inline int cross(const SPoint* a,const SPoint* b) {
    return a->x * b->y - a->y * b->x;
}

static inline SPoint* vsub(const SPoint* a,const SPoint* b, SPoint* res) {
    res->x = a->x - b->x;
    res->y = a->y - b->y;
    return res;
}


static int line_sect(const SPoint* x0,const SPoint* x1,const SPoint* y0,const SPoint* y1, SPoint* res) {
    SPoint dx, dy, d;
    vsub(x1, x0, &dx);
    vsub(y1, y0, &dy);
    vsub(x0, y0, &d);
    float dyx = (float)cross(&dy, &dx);
    if (!dyx) return 0;
    dyx = cross(&d, &dx) / dyx;
    if (dyx <= 0 || dyx >= 1) return 0;
    res->x = int(y0->x + dyx * dy.x);
    res->y = int(y0->y + dyx * dy.y);
    return 1;
}

static int left_of(const SPoint* a,const SPoint* b,const SPoint* c) {
    SPoint tmp1, tmp2;
    int x;
    vsub(b, a, &tmp1);
    vsub(c, b, &tmp2);
    x = cross(&tmp1, &tmp2);
    return x < 0 ? -1 : x > 0;
}

static void poly_edge_clip(const Polygon* sub,const  SPoint* x0,const  SPoint* x1, int left, Polygon* res) {
    int i, side0, side1;
    SPoint tmp;
    const SPoint* v0 = sub->pt+ sub->n - 1;
    const SPoint* v1;
    res->clear();

    side0 = left_of(x0, x1, v0);
    if (side0 != -left) res->add(*v0);

    for (i = 0; i < sub->n; i++) {
        v1 = sub->pt + i;
        side1 = left_of(x0, x1, v1);
        if (side0 + side1 == 0 && side0)
            /* last point and current straddle the edge */
            if (line_sect(x0, x1, v0, v1, &tmp))
                res->add(tmp);
        if (i == sub->n - 1) break;
        if (side1 != -left) res->add(*v1);
        v0 = v1;
        side0 = side1;
    }
}

static int poly_winding(const Polygon* p) {
    return left_of(p->pt, p->pt + 1, p->pt + 2);
}


void intersectPolygonSHPC(const Polygon * sub, const Polygon* clip, Polygon* res)
{
    int i;
    Polygon P1,P2;
    Polygon *p1 = &P1;
    Polygon *p2 = &P2;
    Polygon *tmp;

    int dir = poly_winding(clip);
    poly_edge_clip(sub, clip->pt + clip->n - 1, clip->pt, dir, p2);
    for (i = 0; i < clip->n - 1; i++) {
        tmp = p2; p2 = p1; p1 = tmp;
        if(p1->n == 0) {
            p2->n = 0;
            break;
        }
        poly_edge_clip(p1, clip->pt + i, clip->pt + i + 1, dir, p2);
    }
    res->clear();
    for (i = 0 ; i < p2->n ; i++) res->add(p2->pt[i]);
}

void intersectPolygonSHPC(const Polygon & sub,const Polygon& clip,Polygon& res) {
    intersectPolygonSHPC(&sub, &clip, &res);
}

// 线,包括线段和直线
Line::Line(SPoint a, SPoint b, bool _is_seg)
{
    s = a; e = b; is_seg = _is_seg;
}

Line::Line() {}


//若点a大于点b,即点a在点b顺时针方向,返回true,否则返回false
bool PointCmp(const SPoint &a,const SPoint &b,const SPoint &center)
{
    if (a.x >= 0 && b.x < 0)
        return true;
    if (a.x == 0 && b.x == 0)
        return a.y > b.y;
    //向量OA和向量OB的叉积
    int det = (a.x - center.x) * (b.y - center.y) - (b.x - center.x) * (a.y - center.y);
    if (det < 0)
        return true;
    if (det > 0)
        return false;
    //向量OA和向量OB共线，以距离判断大小
    int d1 = (a.x - center.x) * (a.x - center.x) + (a.y - center.y) * (a.y - center.y);
    int d2 = (b.x - center.x) * (b.x - center.y) + (b.y - center.y) * (b.y - center.y);
    return d1 > d2;
}

SPoint ClockwiseSortPoints(std::vector<SPoint> &vPoints)
{
    //计算重心
    SPoint center;
    double x = 0,y = 0;
    for (int i = 0;i < vPoints.size();i++)
    {
        x += vPoints[i].x;
        y += vPoints[i].y;
    }
    center.x = (int)x/vPoints.size();
    center.y = (int)y/vPoints.size();

    //冒泡排序
    for(int i = 0;i < vPoints.size() - 1;i++)
    {
        for (int j = 0;j < vPoints.size() - i - 1;j++)
        {
            if (PointCmp(vPoints[j],vPoints[j+1],center))
            {
                SPoint tmp = vPoints[j];
                vPoints[j] = vPoints[j + 1];
                vPoints[j + 1] = tmp;
            }
        }
    }
    return center;
}

// 点的加法
SPoint add(const SPoint& lhs, const SPoint& rhs)
{
    SPoint res;

    res.x = lhs.x + rhs.x;
    res.y = lhs.y + rhs.y;
    res.z = lhs.z + rhs.z;

    return res;
}
// 点的减法
SPoint sub(const SPoint& lhs, const SPoint& rhs)
{
    SPoint res;

    res.x = lhs.x - rhs.x;
    res.y = lhs.y - rhs.y;
    res.z = lhs.z - rhs.z;

    return res;
}
// 向量的乘法
SPoint mul(const SPoint& p, double ratio)
{
    SPoint res;

    res.x = p.x * ratio;
    res.y = p.y * ratio;
    res.z = p.z * ratio;

    return res;
}
// 向量的除法
SPoint div(const SPoint& p, double ratio)
{
    SPoint res;

    res.x = p.x / ratio;
    res.y = p.y / ratio;
    res.z = p.z / ratio;

    return res;
}
// 点判断相等
bool equal(const SPoint& lhs, const SPoint& rhs)
{
    return(lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
}

// 1.2、矢量的长度
//
// 参数： vec 矢量
//
double length(const SPoint& vec)
{
    return (sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)));
}

// 1.3、矢量标准化（矢量的长度规约到1）
//
// 参数： vec ： 矢量
//
SPoint normalize(const SPoint& vec)
{
    SPoint res;

    res = div(vec, length(vec));

    return res;
}

// 1.4、矢量点乘
//
// 参数：(p1-op)为矢量1，（p2-op）为矢量2
//
double dotMultiply(const SPoint& op, const SPoint& p1, const SPoint& p2)
{
    return ((p1.x - op.x) * (p2.x - op.x) + (p1.y - op.y) * (p2.y - op.y) + (p1.z - op.z) * (p2.z - op.z));
}
// 参数：vec1为矢量1，vec2为矢量2
//
double dotMultiply(const SPoint& vec1, const SPoint& vec2)
{
    return(vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

// 1.5、矢量叉乘
//
// 参数：(p1-op)为矢量1，（p2-op）为矢量2
//
SPoint multiply(const SPoint& op, const SPoint& p1, const SPoint& p2)
{
    SPoint result;

    result.x = (p1.y - op.y) * (p2.z - op.z) - (p2.y - op.y) * (p1.z - op.z);
    result.y = (p1.z - op.z) * (p2.x - op.x) - (p2.z - op.z) * (p1.x - op.x);
    result.z = (p1.x - op.x) * (p2.y - op.y) - (p2.x - op.x) * (p1.y - op.y);

    return result;
}
// 参数： vec1为矢量1，vec2为矢量2
//
SPoint multiply(const SPoint& vec1, const SPoint& vec2)
{
    SPoint result;

    result.x = vec1.y * vec2.z - vec2.y * vec1.z;
    result.y = vec1.z * vec2.x - vec2.z * vec1.x;
    result.z = vec1.x * vec2.y - vec2.x * vec1.y;

    return result;
}

// 1.9、点是否在线上
// 线分为直线和线段，直线表示的是直线是否经过点
//
// 参数：p : 点  l : 线段或者线
//
bool isponl(const SPoint& p, const Line& l)
{
    SPoint line_vec = sub(l.e, l.s);
    SPoint point_vec1 = sub(p, l.s);
    SPoint point_vec2 = sub(p, l.e);

    SPoint mul_vec = multiply(line_vec, point_vec1);
    double dot = dotMultiply(point_vec1, point_vec2);
    // 点是否在线段上
    if (l.is_seg)
    {
        if (equal(p,l.s) || equal(p,l.e))
            return true;
        return (0.0 == length(mul_vec) && dot < 0.0);

    }
        // 点是否在直线上
    else
    {
        return (0.0 == length(mul_vec));
    }
}

// 1.11、矢量夹角余弦
//

// 参数： vec1 矢量1  vec2 矢量2
//
double Cos(const SPoint& vec1, const SPoint& vec2)
{
    SPoint unit_vec1 = normalize(vec1);
    SPoint unit_vec2 = normalize(vec2);

    return dotMultiply(unit_vec1, unit_vec2);
}

// 参数： op : 矢量公共点 p1 : 矢量1端点 p2 : 矢量2端点
//
double Cos(const SPoint& op, const SPoint& p1, const SPoint& p2)
{
    SPoint vec1 = sub(p1, op);
    SPoint vec2 = sub(p2, op);

    return Cos(vec1, vec2);
}


// 判断两点是否相交
bool isSegIntersect(const Line& l1, const Line& l2, SPoint& inter_p)
{
    SPoint line1 = sub(l1.e, l1.s);
    SPoint line2 = sub(l2.e, l2.s);
    SPoint norm1 = normalize(line1);
    SPoint norm2 = normalize(line2);
    // 线段相交
    if (l1.is_seg)
    {
        // 端点在线段上
        if (isponl(l1.s, l2))
        {
            inter_p = l1.s;
            return true;
        }
        if (isponl(l1.e, l2))
        {
            inter_p = l1.e;
            return true;
        }
        if (isponl(l2.s, l1))
        {
            inter_p = l2.s;
            return true;
        }
        if (isponl(l2.e, l1))
        {
            inter_p = l2.e;
            return true;
        }
        // 判断线段是否相互跨立
        double dot1 = dotMultiply(multiply(sub(l2.s, l1.s), line1), multiply(sub(l2.e, l1.s), line1));
        double dot2 = dotMultiply(multiply(sub(l1.s, l2.s), line2), multiply(sub(l1.e, l2.s), line2));
        if (dot1 < 0.0 && dot2 < 0.0)
        {
            double t1 = length(multiply(sub(l1.s, l2.s), norm2)) / length(multiply(norm2, norm1));
            double t2 = length(multiply(sub(l2.s, l1.s), norm1)) / length(multiply(norm1, norm2));

            inter_p = add(l1.s, mul(norm1, t1));
            return true;
        }
        else
        {
            return false;
        }

    }
        // 直线相交
    else
    {
        if (Cos(line1, line2) == 1.0)
            return false;

        double t1 = length(multiply(sub(l1.s, l2.s), norm2)) / length(multiply(norm2, norm1));
        double t2 = length(multiply(sub(l2.s, l1.s), norm1)) / length(multiply(norm1, norm2));

        inter_p = add(l1.s, mul(norm1, t1));
        return true;
    }
}

// 判断点是否在区域的内部
bool p_inPolygon(Point p, vector<Point> point_vec)
{
    int nCross = 0;
    for (int i = 0; i < point_vec.size(); ++i)
    {
        Point p1(point_vec[i].x, point_vec[i].y);
        Point p2(point_vec[(i+1)%point_vec.size()].x, point_vec[(i+1)%point_vec.size()].y);

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


//int main(int argc, char *argv[])
//{ // 测试点是否在多边形的内部,如果在外部，则求解与中心坐标的相交点坐标
//    std::vector<Point> point_vec;
//    Point p1,p2,p3,p4,p5,p6,p7;
////    [{"x0":404,"y0":260,"x1":690,"y1":66},
////    {"x0":728,"y0":251,"x1":772,"y1":279},
////    {"x0":728,"y0":251,"x1":690,"y1":245},
////    {"x0":952,"y0":465,"x1":332,"y1":245},
//
////    {"x0":241,"y0":527,"x1":308,"y1":27},
////    {"x0":333,"y0":404,"x1":532,"y1":40},
////    {"x0":843,"y0":350,"x1":532,"y1":245}]
//    p1.x = 690;
//    p1.y =66;
////    p2.x = 772;
////    p2.y =279;
//    p3.x = 690;
//    p3.y =245;
//    p4.x = 332;
//    p4.y =245;
//    p5.x = 308;
//    p5.y =27;
//    p6.x = 532;
//    p6.y =40;
//    p7.x = 532;
//    p7.y =245;
//
//    point_vec.push_back(p1);
////    point_vec.push_back(p2);
//    point_vec.push_back(p3);
//    point_vec.push_back(p4);
//    point_vec.push_back(p5);
//    point_vec.push_back(p6);
//    point_vec.push_back(p7);
//
//
//    for (int i = 0; i <point_vec.size() ; ++i)
//    {
//        std::cout << point_vec[i].x << " ";
//    }
//    std::cout << endl;
//    Point p0;
//    p0.x = 817.953796;
//    p0.y = 156.680511;
//    if(!p_inPolygon(p0, point_vec)) // 不在标定区域的内部则处理
//    {
//        Point center;
//        center = ClockwiseSortPoints(point_vec);
//
//        std::cout << p0.x << ":" << p0.y<<endl;
//        std::cout <<  center.x << ":" << center.y<<endl;
//
//        for (int i = 0; i < point_vec.size(); ++i) {
//            std::cout << point_vec[i].x << " ";
//        }
//        std::cout << endl;
//
//        for (int j = 0; j < point_vec.size(); ++j) {
//            Line l1(point_vec[j], point_vec[j + 1], true);
//            Line l2(p0, center, true);
//            Point inter_p;
//            if (isSegIntersect(l1, l2, inter_p)) {
//                std::cout << "inter_p " << inter_p.x << " " << inter_p.y << std::endl;
//                std::cout << point_vec[j].x << " ";
//                std::cout << point_vec[j + 1].x << " ";
//                break;
//            } else {
//                std::cout << point_vec[j].x << " ";
//                std::cout << point_vec[j + 1].x << " ";
//            }
//        }
//    } else
//    {
//        std::cout << "------------ ";
//    }
//
//    return 0;
//}
