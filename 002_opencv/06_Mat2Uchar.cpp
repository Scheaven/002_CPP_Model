#include <opencv2/opencv.hpp>
 
using namespace std;
using namespace cv;
 
/* opencv程序 Mat和Uchar互转 */



/**将Mat类型的数据转换为uchar类型*/
uchar* matToUchar(Mat img)
{
	int img_width = img.cols;
	int img_height = img.rows;
	uchar *p1 = (uchar*)malloc(sizeof(uchar)*img_height*img_width * 3);
	for (int i = 0; i < img_width * img_height * 3; i++)
	{
		p1[i] = (uchar)img.at<Vec3b>(i / (img_width * 3), (i % (img_width * 3)) / 3)[i % 3];
	}
	return p1;
}
 
/**将uchar类型的数据转换为Mat类型*/
Mat ucharToMat(uchar *p2, int img_width, int img_height)
{
	Mat img(Size(img_width, img_height), CV_8UC3);
	for (int i = 0; i < img_width * img_height * 3; i++)
	{
		img.at<Vec3b>(i / (img_width * 3), (i % (img_width * 3)) / 3)[i % 3] = p2[i];
	}
	return img;
}
 
int main()
{
	Mat img = imread("D:\\1.jpg", 1);
	uchar* img_p = matToUchar(img);
	int img_width = img.cols;
	int img_height = img.rows;
	Mat view = ucharToMat(img_p, img_width, img_height);
	imshow("Image view", view);
	cvWaitKey(0);
	cvDestroyWindow("Image view");
}
