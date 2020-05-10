#include "tracker.h"
#include "nn_matching.h"
#include "../encoder_tools/model.h"
#include "linear_assignment.h"
#include <iostream>
using namespace std;

//#define MY_inner_DEBUG
#ifdef MY_inner_DEBUG
#include <string>
#include <iostream>
#endif
// 注意对Eigen 数据结构的使用，CMakeList.txt中需要增加些头文件信息。编译Eigen时，需要增加些参数。否则不能显示调用
DYNAMICM
tracker::iou_cost()
{
    int rows = 3;
    int cols = 5;
    std::<cv::rect> DETECTBOXSS; //存储box信息 ，在源程序（追踪）中不是，自己随便设了一个
    
    DYNAMICM cost_matrix = Eigen::MatrixXf::Zero(rows, cols);
    for(int i = 0; i < rows; i++) {
        int track_idx = 1;
        int csize = 20;
        DETECTBOXSS candidates(csize, 4);
        Eigen::RowVectorXf rowV = (1. - iou(bbox, candidates).array()).matrix().transpose();
        cost_matrix.row(i) = rowV;
    }
    return cost_matrix;
}

Eigen::VectorXf
tracker::iou(DETECTBOX& bbox, DETECTBOXSS& candidates)
{
    float bbox_tl_1 = bbox[0];
    float bbox_tl_2 = bbox[1];
    float bbox_br_1 = bbox[0] + bbox[2];
    float bbox_br_2 = bbox[1] + bbox[3];
    float area_bbox = bbox[2] * bbox[3];

    Eigen::Matrix<float, -1, 2> candidates_tl;
    Eigen::Matrix<float, -1, 2> candidates_br;
    candidates_tl = candidates.leftCols(2) ;
    candidates_br = candidates.rightCols(2) + candidates_tl;

    int size = int(candidates.rows());
    //    Eigen::VectorXf area_intersection(size);
    //    Eigen::VectorXf area_candidates(size);
    Eigen::VectorXf res(size);
    for(int i = 0; i < size; i++) {
        float tl_1 = std::max(bbox_tl_1, candidates_tl(i, 0));
        float tl_2 = std::max(bbox_tl_2, candidates_tl(i, 1));
        float br_1 = std::min(bbox_br_1, candidates_br(i, 0));
        float br_2 = std::min(bbox_br_2, candidates_br(i, 1));

        float w = br_1 - tl_1; w = (w < 0? 0: w);
        float h = br_2 - tl_2; h = (h < 0? 0: h);
        float area_intersection = w * h;
        float area_candidates = candidates(i, 2) * candidates(i, 3);
        res[i] = area_intersection/(area_bbox + area_candidates - area_intersection);
    }
    //#ifdef MY_inner_DEBUG
    //        std::cout << res << std::endl;
    //#endif
    return res;
}

