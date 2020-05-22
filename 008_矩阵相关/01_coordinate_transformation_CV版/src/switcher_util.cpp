//
// Created by Scheaven on 2020/5/20.
//

#include "switcher_util.h"
#include "math_util.h"

CoordSwitcher* CoordSwitcher::instance = NULL;
CoordSwitcher* CoordSwitcher::getInstance(CamVec *CV_Reg)
{
    if(instance==NULL)
    {
        instance = new CoordSwitcher();
//        std::cout << "....---.loading Coord....." << std::endl;
    }
    return instance;
}

CoordSwitcher::CoordSwitcher()
{
//    initHomography(CV_Reg);
}


CoordSwitcher::~CoordSwitcher()
{

}

void CoordSwitcher::initHomography(CamVec *CV_Reg)
{
    for (int i = 0; i < CV_Reg->regInfo[0].count; ++i) {
        point_right_vec.push_back(CV_Reg->regInfo[0].point[i]);
    }
    for (int i = 0; i < CV_Reg->regInfo[1].count; ++i) {
        point_left_vec.push_back(CV_Reg->regInfo[1].point[i]);
    }

//    point_left_vec.push_back(cv::Point2f(326.36f, 64.45f));
//    point_left_vec.push_back(cv::Point2f(339.16f, 128.24f));
//    point_left_vec.push_back(cv::Point2f(313.73f, 255.86f));
//    point_left_vec.push_back(cv::Point2f(275.41f, 183.80f));

//    point_right_vec.push_back(CV_Reg->regInfo[0].point[0]);
//    point_right_vec.push_back(CV_Reg->regInfo[0].pointB);
//    point_right_vec.push_back(CV_Reg->regInfo[0].pointC);
//    point_right_vec.push_back(CV_Reg->regInfo[0].pointD);

    float reprojThresh = 4.0;

    inliers=vector<uchar>(point_left_vec.size(),0);
    //    this->homography = cv::findHomography(point_right_vec, point_left_vec,  inliers, CV_FM_RANSAC, 1.0 );
    this->homography = cv::findHomography(point_right_vec, point_left_vec, CV_RANSAC, reprojThresh); // 用右侧的还原左侧的矩阵

//    std::cout<< this->homography << std::endl;
}

float CoordSwitcher::compare(cv::Point2f A, cv::Point2f B)
{
    cv::Point2f rightPoint = A;
    cv::Point2f leftPoint;
    leftPoint = getTransformPoint(rightPoint, this->homography);

    float distance = calDistance(leftPoint, B);

//    std::cout<< distance << "----A L P--" << leftPoint << std::endl;
    return distance;
}

//比较A点和B点是否是同一个人 , 用距离的评分来获得
float CoordSwitcher::compare(float Ax, float Ay, float Bx, float By)
{
    cv::Point2f rightPoint = cv::Point2f(Ax, Ay);
    cv::Point2f leftPoint;
    leftPoint = getTransformPoint(rightPoint, this->homography);

//    std::cout<< "----L P--" << leftPoint << std::endl;
    return 0.0;

}

//计算原始图像点位在经过矩阵变换后在目标图像上对应位置
cv::Point2f CoordSwitcher::getTransformPoint(const cv::Point2f rightPoint, const cv::Mat &transformMaxtri)
{
    cv::Mat rightP, leftP;
    rightP = (cv::Mat_<double>(3, 1) << rightPoint.x,rightPoint.y,1.0);
    leftP = transformMaxtri * rightP;
    float x = leftP.at<double>(0,0) / leftP.at<double>(2,0);
    float y = leftP.at<double>(1,0) / leftP.at<double>(2,0);
    return cv::Point2f(x, y);
}



