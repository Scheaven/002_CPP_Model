//
// Created by Scheaven on 2020/5/20.
//

#ifndef INC_01_COORDINATE_TRANSFORMATION_SWITCHER_UTIL_H
#define INC_01_COORDINATE_TRANSFORMATION_SWITCHER_UTIL_H

#include "opencv2/opencv.hpp"
#pragma comment(lib, "opencv_core249.lib")

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <math.h>
#include "stdio.h"
#include "stdlib.h"
#include "../con_target.h"

using namespace std;
using namespace cv;

class CoordSwitcher
{
private:
    vector<uchar> inliers;
    vector<cv::Point2f> point_left_vec , point_right_vec;
    cv::Mat homography;
    static CoordSwitcher* instance;
public:
    void initHomography(CamVec *CV_Reg); //构建单应性转换矩阵
    static CoordSwitcher* getInstance(CamVec *CV_Reg);
    CoordSwitcher(); // 初始化，将传递过来的参数初始化，生成单应性转换矩阵
    CoordSwitcher(CamVec *CV_Reg); // 初始化，将传递过来的参数初始化，生成单应性转换矩阵
    ~CoordSwitcher();

    // 转换坐标
    cv::Point2f getTransformPoint(const cv::Point2f rightPoint, const cv::Mat &transformMaxtri);

    float compare(cv::Point2f A, cv::Point2f B);
    float compare(float Ax, float Ay, float Bx, float By);
};



#endif //INC_01_COORDINATE_TRANSFORMATION_SWITCHER_UTIL_H
