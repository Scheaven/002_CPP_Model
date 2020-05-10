//
// Created by Scheaven on 2019/11/18.
//
#ifdef __cplusplus //
extern "C"
{
#endif
#include "h_interface.h"
#include "std_target.h"
#include "sdk.h"
#ifdef __cplusplus //
}
#endif
#include <thread>
#include <unistd.h>
#include <cstdlib>

#include <stdio.h>
#include <string.h>
//#ifdef OPENCV
#include <opencv2/opencv.hpp>			// C++
//#pragma comment(lib, "opencv_core249.lib")
//#pragma comment(lib, "opencv_imgproc249.lib")
//#pragma comment(lib, "opencv_highgui249.lib")
//#endif	// OPENCV

using namespace std;
using namespace cv;


int main(int argc, char *argv[])
{
//    //视频流信息
    VideoCapture cap;

    try {
        cap.open("rtsp://admin:a1234567@192.168.5.35:554/h264/ch1/main/av_stream");
       //cap.open("../cs01.avi");
    }catch(exception){
        cout<<"输入视频"<<endl;
        return 0;
    }

    Mat frame, blob;
    Mat frame2, blob2;
    int ii = 0;
    const char *so_path = "../libyolo_tracking.so";
    const char *conf = "../config.json";
    std::cout << "create " << std::endl;
    container::sdk yoloSdk = container::sdk("1");
    int ret = yoloSdk.init(so_path, conf);
    std::cout << "create over" << ret << std::endl;
    int hum_i=0;
    while (true) {
        std::vector<int> cam_ids;
        //读取视频帧
        std::clock_t t_strat0 = std::clock();
        cap >> frame;
        if(ii++%2){
            continue;
        }
        std::clock_t t_strat2 = std::clock();
  //      cout << "t2----"<<t_strat2<<endl;
        if(!frame.empty()){
            std::clock_t t_strat1 = std::clock();
            yoloSdk.run(frame.data, frame.cols, frame.rows, 3);
            std::clock_t t_strat3 = std::clock();
//             cout << "t1----"<<t_strat1 << " t3--" <<t_strat3<<endl;
            
        }else{
            cout << "-----------------------over--" << endl;
            yoloSdk.release();
            //release(handle);
            break;
        }
    }
    return 0;
}
