//
// Created by Scheaven on 2020/4/23.
//

#ifndef INC_01_CPP_SORT_DRAW_UTIL_H
#define INC_01_CPP_SORT_DRAW_UTIL_H
#include "../detecter_tools/yolo_v2_class.hpp"	// imported functions from DLL
#include "../config.h"
#include "result_util.h"

void draw_boxes(cv::Mat& mat_img, std::vector<bbox_t> result_vec); // 給detecter_tools 中的yolo_v2結構中配置的展示

void draw_result(cv::Mat mat_img, FRAME_RESULT& result_vec); // 終止展示結果的draw
void draw_result2(cv::Mat mat_img, FRAME_RESULT& result_vec);
void draw_SDK_result(int cam_id, cv::Mat mat_img, TResult *t_result);

void show_result(std::vector<bbox_t> result_vec);

#endif //INC_01_CPP_SORT_DRAW_UTIL_H
