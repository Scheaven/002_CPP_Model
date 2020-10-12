//
// Created by Scheaven on 2020/4/20.
//

#include "result_util.h"

// 实现detection到result的结果化转换
void switch_result(DETECTIONS& detections, FRAME_RESULT& results_vec)
{
    DETECTBOX tmpbox;
    for (auto &detection : detections)
    {
        RESULT_STRUCT result;
        tmpbox = detection.tlwh;
        result.rect = cv::Rect(tmpbox(0), tmpbox(1), tmpbox(2), tmpbox(3));
        result.confidence = detection.confidence;
//        std::cout << result.rect << std::endl;
        results_vec.push_back(result);
    }
}

float cul_overlap_area(int Ax, int Ay, int Bx, int By, int Cx, int Cy, int Dx, int Dy)
{
    long x1 = Ax>Cx?Ax:Cx;
    long y1 = Ay>Cy?Ay:Cy;
    long x2 = Bx<Dx?Bx:Dx;
    long y2 = By<Dy?By:Dy;

    float w = 0.0>(x2-x1)?0.0:(x2-x1);
    float h = 0.0>(y2-y1)?0.0:(y2-y1);
    float inter_area = w*h;
    float lap_rate = inter_area/((Dx-Cx)*(Dy-Cy));
    return lap_rate;
}


