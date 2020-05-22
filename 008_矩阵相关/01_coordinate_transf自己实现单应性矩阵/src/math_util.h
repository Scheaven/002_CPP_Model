//
// Created by Scheaven on 2020/5/21.
//

#ifndef INC_01_COORDINATE_TRANSFORMATION_MATH_UTIL_H
#define INC_01_COORDINATE_TRANSFORMATION_MATH_UTIL_H
#include <math.h>
#include <stdint.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "stdio.h"
#include "stdlib.h"

using namespace std;

typedef struct _Point
{
public:
    float x;
    float y;
public:
    _Point(float x, float y);
    _Point();
}SPoint2f;

float calDistance(SPoint2f A, SPoint2f B);

#endif //INC_01_COORDINATE_TRANSFORMATION_MATH_UTIL_H
