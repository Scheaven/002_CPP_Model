// Opencv保存摄像头视频为mp4和flv两种格式
// 由于我采用的是opencv4.0,在保存视频的地方遇到了一些坑。
// 首先，原来的VideoWriter_fourcc没有了，需要使用VideoWriter::fourcc()来定义编码，
// 具体的编码类型可以在http://www.fourcc.org/codecs.php中查看
// 例如

// MP4的fourcc编码为int myFourCC = VideoWriter::fourcc('m', 'p', '4', 'v');
// FLV的fourcc编码为int myFourCC = VideoWriter::fourcc('X', 'V', 'I', 'D');

// 写入视频无非是一帧帧写入图像，通过VideoWriter writer("OutFileSavePath", myFourCC, rate, size, true);然后通过writer的writer.write(frame)或者writer << frame;写入视频图像。
// VideoWriter实例化中最后一个参数是指定是否彩色写入,true即为彩色。

// 当实例化VideoWriter出错时，可以根据报错信息改变fourcc的值，或者查看FFmpeg是否安装完善。
// 可以通过ffmpeg.exe -formats来查看ffmpeg支持的格式
// 实例程序
#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include<iostream>
using namespace cv;
using namespace std;
int main()
{
    VideoCapture videoCapture(0);
    Size size = Size(videoCapture.get(CAP_PROP_FRAME_WIDTH), videoCapture.get(CAP_PROP_FRAME_HEIGHT));
    if (size.width <= 0 || size.height <= 0)
    {
        cout << "ERROR while get the width or the height" << endl;
    }
    else {
        cout << "width: " << size.width << "\nheight: " << size.height << endl;
    }
    //int myFourCC = VideoWriter::fourcc('X', 'V', 'I', 'D');//avi
    int myFourCC = VideoWriter::fourcc('m', 'p', '4', 'v');//mp4
    //'m', 'p', '4', 'v'//'F','L','V','1'//'m', 'p', '4','2' //'m','p','4','v'//'d','i','v','x'
    double rate = videoCapture.get(CAP_PROP_FPS); // 可用数字代替 5
    VideoWriter writer("./hello.mp4", myFourCC, rate, size, true);


    //VideoWriter writer;
    //writer.open("./sresult.mp4", -1,25,Size(1000,800),true); //注意，写的大小要与设置的画面一样大，否则写入为空

    if (!videoCapture.isOpened()) {
        cout << "Video not open!" << endl;
        system("pause");
        return 1;
    }

    cout << "FPS:" << rate << endl;
    Mat frame;
    namedWindow("frame", WINDOW_AUTOSIZE);
    while (videoCapture.isOpened())
    {
        bool ret = videoCapture.read(frame);
        if (ret)
        {
            imshow("frame", frame);
            //writer.write(frame);
            writer << frame; // 其后不能添加waitKey(1) 否则不能存储
            if (waitKey(20) > 0)break;
        }
        else {
            break;
        }
    }
    cout << "FINISH ALL WORK----------" << endl;
    videoCapture.release(); //when everything done, release the capture
    writer.release();
    destroyAllWindows();
    system("pause");
    return 0;
}
