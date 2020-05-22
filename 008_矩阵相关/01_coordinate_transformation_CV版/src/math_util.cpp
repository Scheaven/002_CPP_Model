//
// Created by Scheaven on 2020/5/21.
//

#include "math_util.h"

float calDistance(cv::Point2f A, cv::Point2f B)
{
    float x_d , y_d;
    x_d = A.x - B.x;
    y_d = A.y - B.y;
    float lea=sqrt(x_d*x_d + y_d*y_d);
    return lea;
}
