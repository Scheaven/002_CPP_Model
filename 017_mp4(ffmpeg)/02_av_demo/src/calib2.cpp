#include"videoWriterFFmpeg.h"
#include<iostream>
using namespace std;
using namespace cv;
string toString(int a)
{
	char str[10];
	sprintf(str, "%d", a);
	return string(str);
}

/*
这样的话，我们直接进行以下步骤：

1.使用opencv读取图片，或都opencv直接产生图片；

2.opencv对图片进行各种处理并得到Mat类型的BGR数据；

3.opencv的Mat数据转换成yuv420格式数据；

4.由yuv420格式数据转换成ffmpeg的AVFrame；

5.ffmpeg写视频并保存。

以上可以看出，核心部分在于Mat->yuv420->AVFrame，其它都好说，参看代码如下：
————————————————
版权声明：本文为CSDN博主「alpc40」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/weixin_39212021/article/details/80870166

 */
int main()
{
	VideoCapture cap;
	videoWriterFFmpeg videoWriter;
	Mat src;
	// string img_name = "../data/";
	cap.open("/data/disk1/project/data/01_reid/cam_52.avi");

	string video_path = "out.mp4";
	int bitrate = 4500000;
	int fps = 24;
	if (videoWriter.open((char *)video_path.c_str(), bitrate, fps, 800,600) != 0)
		cout << "error" << endl;
	for (int i = 0; i < 400; i++)
	{
		// src = imread(img_name + toString(i) + ".JPG");
		cap >> src;
		// src.resize((400,300));
		cv::resize(src, src, cv::Size(800,600));
		videoWriter.write(src);
		// *writer << src;
		// for (int j = 0; j < 20; j++)
		// {
		// 	cout << "write frame " <<i*20+j+1 << " sucess" << endl;
		// 	videoWriter.write(src);
		// }
	}
	videoWriter.flush();

	return 0;
}

    if (av_dict_set(&options, "movflags", "+frag_keyframe+empty_moov",
0) < 0) {
      std::cout << "av_dict_set empty_moov failed" << std::endl;
      return;
    }

    ret = avformat_write_header(context, &options);










///******************************/
///*        Á¢ÌåÆ¥ÅäºÍ²â¾à        */
///******************************/
//
//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//const int imageWidth = 1600;                             //ÉãÏñÍ·µÄ·Ö±æÂÊ
//const int imageHeight = 1200;
//Size imageSize = Size(imageWidth, imageHeight);
//
//Mat rgbImageL, grayImageL;
//Mat rgbImageR, grayImageR;
//Mat rectifyImageL, rectifyImageR;
//
//Rect validROIL;//Í¼ÏñÐ£ÕýÖ®ºó£¬»á¶ÔÍ¼Ïñ½øÐÐ²Ã¼ô£¬ÕâÀïµÄvalidROI¾ÍÊÇÖ¸²Ã¼ôÖ®ºóµÄÇøÓò
//Rect validROIR;
//
//Mat mapLx, mapLy, mapRx, mapRy;     //Ó³Éä±í
//Mat Rl, Rr, Pl, Pr, Q;              //Ð£ÕýÐý×ª¾ØÕóR£¬Í¶Ó°¾ØÕóP ÖØÍ¶Ó°¾ØÕóQ
//Mat xyz;              //ÈýÎ¬×ø±ê
//
//Point origin;         //Êó±ê°´ÏÂµÄÆðÊ¼µã
//Rect selection;      //¶¨Òå¾ØÐÎÑ¡¿ò
//bool selectObject = false;    //ÊÇ·ñÑ¡Ôñ¶ÔÏó
//
//int blockSize = 0, uniquenessRatio = 0, numDisparities = 0;
//Ptr<StereoBM> bm = StereoBM::create(16, 9);
//
///*
//ÊÂÏÈ±ê¶¨ºÃµÄÏà»úµÄ²ÎÊý
//fx 0 cx
//0 fy cy
//0 0  1
//*/
//Mat cameraMatrixL = (Mat_<double>(3, 3) << 1.3326580049539741e+03, 0., 8.5707693143813731e+02, 0.,
//	1.3328103465314075e+03, 5.8864510013773088e+02, 0., 0., 1.);
////¶ÔÓ¦matlabÀïµÄ×óÏà»ú±ê¶¨¾ØÕó
//Mat distCoeffL = (Mat_<double>(5, 1) << -2.8045130586483613e-01, 2.3793216045311979e-02,
//	1.2707455545866691e-03, -8.5396571769118861e-05,
//	1.5333351218494151e-01);
////¶ÔÓ¦MatlabËùµÃ×óiÏà»ú»û±ä²ÎÊý
//
//Mat cameraMatrixR = (Mat_<double>(3, 3) << 1.3415015304155293e+03, 0., 8.2015522358224712e+02, 0.,
//	1.3405584983867755e+03, 6.2602260787344244e+02, 0., 0., 1.);
////¶ÔÓ¦matlabÀïµÄÓÒÏà»ú±ê¶¨¾ØÕó
//
//Mat distCoeffR = (Mat_<double>(5, 1) << -2.9689673143127382e-01, 1.4135067565749787e-01,
//	-5.2500364253100303e-04, -5.9239444589348561e-06,
//	-5.2601323055946496e-02);
////¶ÔÓ¦MatlabËùµÃÓÒÏà»ú»û±ä²ÎÊý
//
//Mat T = (Mat_<double>(3, 1) << 6.5772611841823936e-001, -1.0384210259014603e+001,
//	-4.3222483571379522e+000);//TÆ½ÒÆÏòÁ¿
//															 //¶ÔÓ¦MatlabËùµÃT²ÎÊý
////Mat rec = (Mat_<double>(3, 1) << -0.00306, -0.03207, 0.00206);//recÐý×ªÏòÁ¿£¬¶ÔÓ¦matlab om²ÎÊý
//Mat R=(Mat_<double>(3,3)<< 9.9992653287053390e-001, -6.5184724487311113e-003,
//	1.0219509697052322e-002, 6.5049975997708192e-003,
//	9.9997792935128083e-001, 1.3512277941784086e-003,
//	-1.0228092086992024e-002, -1.2846506373009731e-003,
//	9.9994686649091513e-001);//R Ðý×ª¾ØÕó
//
//
//	  /*****Á¢ÌåÆ¥Åä*****/
//void stereo_match(int, void*)
//{
//	bm->setBlockSize(2 * blockSize + 5);     //SAD´°¿Ú´óÐ¡£¬5~21Ö®¼äÎªÒË
//	bm->setROI1(validROIL);
//	bm->setROI2(validROIR);
//	bm->setPreFilterCap(31);
//	bm->setMinDisparity(0);  //×îÐ¡ÊÓ²î£¬Ä¬ÈÏÖµÎª0, ¿ÉÒÔÊÇ¸ºÖµ£¬intÐÍ
//	bm->setNumDisparities(numDisparities * 16 + 16);//ÊÓ²î´°¿Ú£¬¼´×î´óÊÓ²îÖµÓë×îÐ¡ÊÓ²îÖµÖ®²î,´°¿Ú´óÐ¡±ØÐëÊÇ16µÄÕûÊý±¶£¬intÐÍ
//	bm->setTextureThreshold(10);
//	bm->setUniquenessRatio(uniquenessRatio);//uniquenessRatioÖ÷Òª¿ÉÒÔ·ÀÖ¹ÎóÆ¥Åä
//	bm->setSpeckleWindowSize(100);
//	bm->setSpeckleRange(32);
//	bm->setDisp12MaxDiff(-1);
//	Mat disp, disp8;
//	bm->compute(rectifyImageL, rectifyImageR, disp);//ÊäÈëÍ¼Ïñ±ØÐëÎª»Ò¶ÈÍ¼
//	disp.convertTo(disp8, CV_8U, 255 / ((numDisparities * 16 + 16)*16.));//¼ÆËã³öµÄÊÓ²îÊÇCV_16S¸ñÊ½
//	reprojectImageTo3D(disp, xyz, Q, true); //ÔÚÊµ¼ÊÇó¾àÀëÊ±£¬ReprojectTo3D³öÀ´µÄX / W, Y / W, Z / W¶¼Òª³ËÒÔ16(Ò²¾ÍÊÇW³ýÒÔ16)£¬²ÅÄÜµÃµ½ÕýÈ·µÄÈýÎ¬×ø±êÐÅÏ¢¡£
//	xyz = xyz * 16;
//	imshow("disparity", disp8);
//}
//
///*****ÃèÊö£ºÊó±ê²Ù×÷»Øµ÷*****/
//static void onMouse(int event, int x, int y, int, void*)
//{
//	if (selectObject)
//	{
//		selection.x = MIN(x, origin.x);
//		selection.y = MIN(y, origin.y);
//		selection.width = std::abs(x - origin.x);
//		selection.height = std::abs(y - origin.y);
//	}
//
//	switch (event)
//	{
//	case EVENT_LBUTTONDOWN:   //Êó±ê×ó°´Å¥°´ÏÂµÄÊÂ¼þ
//		origin = Point(x, y);
//		selection = Rect(x, y, 0, 0);
//		selectObject = true;
//		cout << origin << "in world coordinate is: " << xyz.at<Vec3f>(origin) << endl;
//		break;
//	case EVENT_LBUTTONUP:    //Êó±ê×ó°´Å¥ÊÍ·ÅµÄÊÂ¼þ
//		selectObject = false;
//		if (selection.width > 0 && selection.height > 0)
//			break;
//	}
//}
//
//Mat scaleMat(Mat src, Size sz)
//{
//	Size src_sz = src.size();
//	if (src_sz == sz)
//		return src;
//	Mat dst;
//	float scale = min(float(src_sz.height) / sz.height, float(src_sz.width) / sz.width);
//	resize(src, dst, Size(), 1.0 / scale, 1.0 / scale);
//	return dst(Rect(0, 0, sz.width, sz.height));
//}
//
///*****Ö÷º¯Êý*****/
//int main()
//{
//	/*
//	Á¢ÌåÐ£Õý
//	*/
//	//Rodrigues(rec, R); //Rodrigues±ä»»
//	stereoRectify(cameraMatrixL, distCoeffL, cameraMatrixR, distCoeffR, imageSize, R, T, Rl, Rr, Pl, Pr, Q, 0,
//		0, imageSize, &validROIL, &validROIR);
//	initUndistortRectifyMap(cameraMatrixL, distCoeffL, Rl, Pr, imageSize, CV_32FC1, mapLx, mapLy);
//	initUndistortRectifyMap(cameraMatrixR, distCoeffR, Rr, Pr, imageSize, CV_32FC1, mapRx, mapRy);
//
//	/*
//	¶ÁÈ¡Í¼Æ¬
//	*/
//
//	rgbImageL = imread("../calib/13m1/13.bmp", CV_LOAD_IMAGE_COLOR);
//	cvtColor(rgbImageL, grayImageL, CV_BGR2GRAY);
//	rgbImageR = imread("../calib/2m1/2.bmp", CV_LOAD_IMAGE_COLOR);
//	cvtColor(rgbImageR, grayImageR, CV_BGR2GRAY);
//	Size imgSize = Size(1600, 1200);
//	rgbImageL = scaleMat(rgbImageL, imgSize);
//	rgbImageR = scaleMat(rgbImageR, imgSize);
//	imshow("ImageL Before Rectify", grayImageL);
//	imshow("ImageR Before Rectify", grayImageR);
//
//	/*
//	¾­¹ýremapÖ®ºó£¬×óÓÒÏà»úµÄÍ¼ÏñÒÑ¾­¹²Ãæ²¢ÇÒÐÐ¶Ô×¼ÁË
//	*/
//	remap(grayImageL, rectifyImageL, mapLx, mapLy, INTER_LINEAR);
//	remap(grayImageR, rectifyImageR, mapRx, mapRy, INTER_LINEAR);
//
//	/*
//	°ÑÐ£Õý½á¹ûÏÔÊ¾³öÀ´
//	*/
//	Mat rgbRectifyImageL, rgbRectifyImageR;
//	cvtColor(rectifyImageL, rgbRectifyImageL, CV_GRAY2BGR);  //Î±²ÊÉ«Í¼
//	cvtColor(rectifyImageR, rgbRectifyImageR, CV_GRAY2BGR);
//	resize(rgbRectifyImageL, rgbRectifyImageL, Size(), 0.25, 0.25);
//	resize(rgbRectifyImageR, rgbRectifyImageR, Size(), 0.25, 0.25);
//	//µ¥¶ÀÏÔÊ¾
//	//rectangle(rgbRectifyImageL, validROIL, Scalar(0, 0, 255), 3, 8);
//	//rectangle(rgbRectifyImageR, validROIR, Scalar(0, 0, 255), 3, 8);
//	imshow("ImageL After Rectify", rgbRectifyImageL);
//	imshow("ImageR After Rectify", rgbRectifyImageR);
//
//	//ÏÔÊ¾ÔÚÍ¬Ò»ÕÅÍ¼ÉÏ
//	Mat canvas;
//	double sf;
//	int w, h;
//	sf = 600. / MAX(imageSize.width, imageSize.height);
//	w = cvRound(imageSize.width * sf);
//	h = cvRound(imageSize.height * sf);
//	canvas.create(h, w * 2, CV_8UC3);   //×¢ÒâÍ¨µÀ
//
//										//×óÍ¼Ïñ»­µ½»­²¼ÉÏ
//	Mat canvasPart = canvas(Rect(w * 0, 0, w, h));                                //µÃµ½»­²¼µÄÒ»²¿·Ö
//	resize(rgbRectifyImageL, canvasPart, canvasPart.size(), 0, 0, INTER_AREA);     //°ÑÍ¼ÏñËõ·Åµ½¸úcanvasPartÒ»Ñù´óÐ¡
//	Rect vroiL(cvRound(validROIL.x*sf), cvRound(validROIL.y*sf),                //»ñµÃ±»½ØÈ¡µÄÇøÓò
//		cvRound(validROIL.width*sf), cvRound(validROIL.height*sf));
//	//rectangle(canvasPart, vroiL, Scalar(0, 0, 255), 3, 8);                      //»­ÉÏÒ»¸ö¾ØÐÎ
//	cout << "Painted ImageL" << endl;
//
//	//ÓÒÍ¼Ïñ»­µ½»­²¼ÉÏ
//	canvasPart = canvas(Rect(w, 0, w, h));                                      //»ñµÃ»­²¼µÄÁíÒ»²¿·Ö
//	resize(rgbRectifyImageR, canvasPart, canvasPart.size(), 0, 0, INTER_LINEAR);
//	Rect vroiR(cvRound(validROIR.x * sf), cvRound(validROIR.y*sf),
//		cvRound(validROIR.width * sf), cvRound(validROIR.height * sf));
//	//rectangle(canvasPart, vroiR, Scalar(0, 0, 255), 3, 8);
//	cout << "Painted ImageR" << endl;
//
//	//»­ÉÏ¶ÔÓ¦µÄÏßÌõ
//	for (int i = 0; i < canvas.rows; i += 16)
//		line(canvas, Point(0, i), Point(canvas.cols, i), Scalar(0, 255, 0), 1, 8);
//	imshow("rectified", canvas);
//
//	/*
//	Á¢ÌåÆ¥Åä
//	*/
//	namedWindow("disparity", CV_WINDOW_AUTOSIZE);
//	// ´´½¨SAD´°¿Ú Trackbar
//	createTrackbar("BlockSize:\n", "disparity", &blockSize, 8, stereo_match);
//	// ´´½¨ÊÓ²îÎ¨Ò»ÐÔ°Ù·Ö±È´°¿Ú Trackbar
//	createTrackbar("UniquenessRatio:\n", "disparity", &uniquenessRatio, 50, stereo_match);
//	// ´´½¨ÊÓ²î´°¿Ú Trackbar
//	createTrackbar("NumDisparities:\n", "disparity", &numDisparities, 16, stereo_match);
//	//Êó±êÏìÓ¦º¯ÊýsetMouseCallback(´°¿ÚÃû³Æ, Êó±ê»Øµ÷º¯Êý, ´«¸ø»Øµ÷º¯ÊýµÄ²ÎÊý£¬Ò»°ãÈ¡0)
//	setMouseCallback("disparity", onMouse, 0);
//	stereo_match(0, 0);
//
//	waitKey(0);
//	return 0;
//}
