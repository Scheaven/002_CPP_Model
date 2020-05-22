//
// Created by Scheaven on 2020/5/22.
//

#ifndef INC_02_COORDINATE_TRANSFORMATION_HOMOGRAPHY_UTIL_H
#define INC_02_COORDINATE_TRANSFORMATION_HOMOGRAPHY_UTIL_H

#include <vector>
#include "math_util.h"

static void gaussian_elimination(float *input, int n);
void creatHomography();
void creatHomography(vector<SPoint2f> src, vector<SPoint2f> dst,float homography[3][3]);


#endif //INC_02_COORDINATE_TRANSFORMATION_HOMOGRAPHY_UTIL_H
