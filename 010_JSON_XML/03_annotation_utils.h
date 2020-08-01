//
// Created by Scheaven on 2020/7/28.
//

#ifndef DEMO_ANNOTATION_UTILS_H
#define DEMO_ANNOTATION_UTILS_H

#include <iostream>
#include <vector>
#include "string"
#include "fstream"
#include "../xml_tools/tinyxml.h"
#include <opencv2/opencv.hpp>
#pragma comment(lib, "opencv_core249.lib")
#pragma comment(lib, "opencv_imgproc249.lib")
#pragma comment(lib, "opencv_highgui249.lib")

using namespace std;
using namespace cv;

typedef struct _Box_Info
{
    char* name;
    float prob;
    int xmin;
    int ymin;
    int xmax;
    int ymax;
}Box_Info;

typedef struct _XML_Info
{
    char* fileName;
    char* filePath;

    int img_w;
    int img_h;
    int img_depth;

    Box_Info* boxInfo;
    int box_count;
}XML_Info;

int readXML(string fileName);
void Create_VOCXML(string fileName,XML_Info* xmlInfo);
void add_NodeXML(string path, XML_Info* xmlInfo);



#endif //DEMO_ANNOTATION_UTILS_H
