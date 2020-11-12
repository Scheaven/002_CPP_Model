#include <iostream>
#include <iostream>
#include <vector>
#ifdef OPENCV
#include <opencv2/opencv.hpp>			// C++
#pragma comment(lib, "opencv_core249.lib")
#pragma comment(lib, "opencv_imgproc249.lib")
#pragma comment(lib, "opencv_highgui249.lib")

#endif	// OPENCV

using namespace cv;

//------------------------------------------------------------------------
// Mouse callbacks
//------------------------------------------------------------------------
void mv_MouseCallback(int event, int x, int y, int /*flags*/, void* param)
{
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        cv::Point2f* p = (cv::Point2f*) param;
        if (p)
        {
            p->x = static_cast<float>(x);
            p->y = static_cast<float>(y);
        }
    }
}

int main(int argc,char** argv)
{
    int k = 0;
    cv::namedWindow("Video");
    cv::Mat frame = cv::Mat(800, 800, CV_8UC3);
    // Set mouse callback
    cv::Point2f pointXY;
    cv::setMouseCallback("Video", mv_MouseCallback, (void*)&pointXY);

    while (k != 27)
    {
        frame = cv::Scalar::all(0);
        
       cv::circle(frame, pointXY, 1, cv::Scalar(0, 255, 0), 1, CV_AA);

        cv::imshow("Video", frame);
        k = cv::waitKey(1);
    }

    std::cout<<"Hello, World!"<<std::endl;
    return 0;
}

