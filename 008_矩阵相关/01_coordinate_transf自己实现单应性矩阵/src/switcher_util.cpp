//
// Created by Scheaven on 2020/5/20.
//

#include "switcher_util.h"


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

    float reprojThresh = 4.0;

    creatHomography(point_right_vec, point_left_vec, this->s_homography);

    std::cout <<  this->s_homography <<  "---" << std::endl;

}

float CoordSwitcher::compare(SPoint2f A, SPoint2f B)
{
    SPoint2f rightPoint = A;
    SPoint2f leftPoint;
    leftPoint = getTransPoint(rightPoint, this->s_homography);

    float distance = calDistance(leftPoint, B);

    std::cout<< "----A L P--" << leftPoint.x << std::endl;
    return distance;
}

//计算原始图像点位在经过矩阵变换后在目标图像上对应位置
SPoint2f CoordSwitcher::getTransPoint(const SPoint2f rightPoint, const float transformMaxtri[3][3])
{
    float rightP[3][1], leftP[3][1];
    rightP[0][0] = rightPoint.x;
    rightP[1][0] = rightPoint.y;
    rightP[2][0] = 1.0;
    for(int i=0;i<3;++i){//矩阵c=a*b
        for(int j=0;j<1;++j){
            leftP[i][j]=0;
            for(int k=0;k<3;++k){
                leftP[i][j]+=transformMaxtri[i][k]*rightP[k][j];
            }
        }
    }

    float x = leftP[0][0] / leftP[2][0];
    float y = leftP[1][0] / leftP[2][0];
    return SPoint2f(x, y);
}
