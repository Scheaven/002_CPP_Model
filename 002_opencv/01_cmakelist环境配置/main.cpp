//
// Created by Scheaven on 2019/11/18.
//
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <map>
#include <string>
#include <list>
#include <algorithm>

using namespace std;
using namespace cv;

int main(int argc, char *argv[]){
    //视频流信息
    VideoCapture cap;
//    VideoCapture out_cap;

    try {
        cap.open("../data/cs01.avi");
    }catch(exception){
        cout<<"输入视频"<<endl;
        return 0;
    }
    //获得帧的宽高
    int img_w = static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH));
    int img_h = static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT));
    string out_flie = "../result.mp4";
    Size S(img_w, img_h);
    //获得帧率
    double rate = cap.get(CAP_PROP_FPS);
    //打开视频文件，准备写入
    //int myFourCC = VideoWriter::fourcc('X', 'V', 'I', 'D');//avi
    int FourCC = VideoWriter::fourcc('m', 'p', '4', 'v');//mp4
    //'m', 'p', '4', 'v'//'F','L','V','1'//'m', 'p', '4','2' //'m','p','4','v'//'d','i','v','x'
    VideoWriter out_cap(out_flie, FourCC, rate, S, true);
    Mat frame;

    while (true){
        //读取视频帧
        cap >> frame;

        if(!frame.empty()){
            out_cap.write(frame);
            cout << "--ok--" << endl;
        }else{
            cout << "--over--" << endl;
            break;
        }

//        waitKey(1);
    }
    return 0;


}
