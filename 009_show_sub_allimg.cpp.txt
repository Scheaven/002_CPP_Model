#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

vector<Mat> read_images_in_folder(cv::String pattern);

int main()
{
    cv::String pattern = "G:/temp_picture/*.jpg";
    vector<Mat> images = read_images_in_folder(pattern);

    return 0;   
}

vector<Mat> read_images_in_folder(cv::String pattern)
{
    vector<cv::String> fn;
    glob(pattern, fn, false);

    vector<Mat> images;
    size_t count = fn.size(); //number of png files in images folder
    for (size_t i = 0; i < count; i++)
    {
        images.push_back(imread(fn[i]));
        imshow("img", imread(fn[i]));
        waitKey(1000);
    }
    return images;
}

//opencv自带函数glob()遍历
//OpenCV自带一个函数glob()可以遍历文件，如果用这个函数的话，遍历文件也是非常简单的。这个函数非常强大，人脸识别的时候用这个函数应该会比用at.txt更加方便。一个参考示例如下。