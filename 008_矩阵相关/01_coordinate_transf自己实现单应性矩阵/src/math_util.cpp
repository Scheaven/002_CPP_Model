//
// Created by Scheaven on 2020/5/21.
//

#include "math_util.h"

SPoint2f::_Point(float x, float y)
{
    this->x = x;
    this->y = y;
}

SPoint2f::_Point()
{

}

float calDistance(SPoint2f A, SPoint2f B)
{
    float x_d , y_d;
    x_d = A.x - B.x;
    y_d = A.y - B.y;
    float lea = sqrt(x_d*x_d + y_d*y_d);
    return lea;
}


//int main()
//{
//    SPoint2f A(100.0f, 100.0f);
//    SPoint2f B(10.0f, 10.0f) ;
//    float confidence = calDistance(A, B);
//    std::cout << confidence <<"-=-=-=-" << std::endl;
//    SPoint2f *regA_point = (SPoint2f*)malloc(sizeof(SPoint2f)*4);
//    std::cout << confidence <<"-=-=-=-" << std::endl;
//
//}