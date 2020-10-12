//
// Created by Scheaven on 2020/4/23.
//

#include "draw_util.h"

#ifdef OPENCV
#include <opencv2/opencv.hpp>			// C++
#pragma comment(lib, "opencv_core249.lib")
#pragma comment(lib, "opencv_imgproc249.lib")
#pragma comment(lib, "opencv_highgui249.lib")
#endif	// OPENCV
using namespace cv;
//int myFourCC = VideoWriter::fourcc('m','p','4','v');
//cv::VideoWriter writer;
cv::VideoWriter writer("./sresult.avi", CV_FOURCC('M','J','P','G'), 10, cv::Size(800,500), true);
cv::VideoWriter writer2("./sresult2.avi", CV_FOURCC('M','J','P','G'), 10, cv::Size(800,500), true);

void draw_boxes(cv::Mat& mat_img, std::vector<bbox_t> result_vec)
{
    for (auto &i : result_vec) {
        if(i.obj_id == 0){
            cv::rectangle(mat_img, cv::Rect(i.x, i.y, i.w, i.h), cv::Scalar(50, 200, 50), 1);
            cv::putText(mat_img,std::to_string(i.prob),Point(i.x,i.y),CV_FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255,255,0), 2);
        }
    }
//    cv::imshow("window name", mat_img);
    cv::resize(mat_img,mat_img,cv::Size(800,500));
    writer << mat_img;
//    cv::waitKey(0);
}

void draw_result(cv::Mat mat_img, FRAME_RESULT& result_vec)
{
    for (auto &result : result_vec) {
        cv::rectangle(mat_img, result.rect , cv::Scalar(50, 200, 50), 1);
        cv::putText(mat_img, std::to_string(result.human_id), Point(result.rect.x,result.rect.y), CV_FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255,255,0), 2);
    }
    printf("---==========================-----------");
//    delete tmp_rect;
    cv::resize(mat_img,mat_img,cv::Size(800,500));
    //    cv::imwrite("1111.jpg", mat_img);
    cv::imshow("RESULT", mat_img);
//        writer<< mat_img;
    cv::waitKey(1);
}

void draw_result2(cv::Mat mat_img, FRAME_RESULT& result_vec)
{
    printf("---==========================-----------");
    for (auto &result : result_vec) {
        cv::rectangle(mat_img, result.rect , cv::Scalar(50, 200, 50), 1);
        cv::putText(mat_img, std::to_string(result.human_id), Point(result.rect.x,result.rect.y), CV_FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255,255,0), 2);
    }
//    delete tmp_rect;
    cv::resize(mat_img,mat_img,cv::Size(800,500));
    //    cv::imwrite("1111.jpg", mat_img);
    cv::imshow("RESULT", mat_img);
//        writer<< mat_img;
    cv::waitKey(1);
}

void draw_SDK_result(int cam_id, cv::Mat mat_img, TResult *t_result)
{
    cv::Rect tmp_rect;
//    std::cout<<t_result->targets[0].id<<"count" <<t_result->count << std::endl;

    for (int i = 0; i < t_result->count; ++i) {
        auto &result = t_result->targets[i];
        tmp_rect = cv::Rect(result.rect.left,result.rect.top,result.rect.right-result.rect.left,result.rect.bottom-result.rect.top);
        cv::rectangle(mat_img, tmp_rect , cv::Scalar(50, 200, 50), 2);
        cv::putText(mat_img, std::to_string(result.id), Point(result.rect.left,result.rect.top), CV_FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255,255,0), 2);
//        cv::putText(mat_img, std::to_string(result.confidence), Point(result.rect.left+100,result.rect.top), CV_FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255,255,0), 2);
        if(result.rect.top<0)
        {
            cv::putText(mat_img, std::to_string(0000), Point(result.rect.left-100,result.rect.top+100), CV_FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255,255,0), 2);
        }else
            cv::putText(mat_img, result.attribute, Point(result.rect.left-100,result.rect.top+100), CV_FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255,255,0), 2);

    }
//    delete tmp_rect;
    cv::resize(mat_img, mat_img, cv::Size(800,500));
    if(cam_id==1)
    {
        //    cv::imwrite("1111.jpg", mat_img);
    cv::imshow("RESULT", mat_img);
//        writer<< mat_img;
    cv::waitKey(1);
    }else if(cam_id==0)
    {
//    cv::imwrite("1111.jpg", mat_img);
    cv::imshow("RESULT", mat_img);
//        writer2<< mat_img;
    cv::waitKey(1);
    }

}

void show_result(std::vector<bbox_t> result_vec)
{
    std::cout<< result_vec.size() << std::endl;
    for (auto &i : result_vec) {
        if(i.obj_id == 0) {
            std::cout << "obj_id = " << i.obj_id << " - x = " << i.x << ", y = " << i.y
                      << ", w = " << i.w << ", h = " << i.h
                      << ", prob = " << i.prob << std::endl;
        }
    }
}