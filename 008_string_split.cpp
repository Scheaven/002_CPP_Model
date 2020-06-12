/*
    输入一连串数字，数字之间逗号隔开，把数字存到数组或者向量里。
*/

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

int main()
{
    string str_input;
    cout<<"输入一串以逗号为分隔符的数字字符串："<<endl;
    while(cin>>str_input)
    {
        vector<int> nums;
        // string->char *
        char *s_input = (char *)str_input.c_str();
        const char * split = ",";
        // 以逗号为分隔符拆分字符串
        char *p = strtok(s_input, split);

        int a;
        while(p != NULL)
        {
            // char * -> int
            sscanf(p, "%d", &a);
            nums.push_back(a);
            p=strtok(NULL, split);
        }

        cout<<"输出得到的数字："<<endl;
        for(a = 0; a < nums.size(); a++)
        {
            cout<<nums[a]<<endl;
        }
    }
    return 0;
}

/** 分割特征样例
std::vector<int> TrackerManager::read_tracker(string in_path)
{
    char *s_input;
    const char * split = ",";
    // 以逗号为分隔符拆分字符串
    char *p;
    int x;
    int y;
    int w;
    int h;
    float a;

    ifstream in(in_path);
    string filename;
    string line;

    if(in) // 有该文件
    {
        std::vector<cv::Rect> boxes;
        std::vector<vector<float> > feats_vec;
        while (getline (in, line)) // line中不包括每行的换行符
        {
            cv::Rect rect;
            vector<float> feats;

            s_input = (char *)line.c_str();
            // 以逗号为分隔符拆分字符串
            p = strtok(s_input, split);

            // char * -> int
            sscanf(p, "%d", &x);
            p=strtok(NULL, split);
            sscanf(p, "%d", &y);
            p=strtok(NULL, split);
            sscanf(p, "%d", &w);
            p=strtok(NULL, split);
            sscanf(p, "%d", &h);
            p=strtok(NULL, split);
//                    boxes2.push_back(cv::Rect(x,y,w,h));
//                    DetecterManager::getInstance()->encoder_features(boxes2, detections);

            rect.x = x;
            rect.y = y;
            rect.width = w;
            rect.height = h;//DETECTBOX(x, y, w, h);

            getline (in, line);

            s_input = (char *)line.c_str();
            // 以逗号为分隔符拆分字符串
            p = strtok(s_input, split);

            for(int j = 0; j < 128; j++) {
                sscanf(p, "%f", &a);
                feats.push_back(a);
                p=strtok(NULL, split);
            }
            boxes.push_back(rect);
            feats_vec.push_back(feats);
        }
//        return single_tracker(1, boxes, feats_vec);
        std::vector<int> tem_vec;
        return tem_vec;

    }
    else // 没有该文件
    {
        cout <<"-- no such file" << endl;
    }
}
*/