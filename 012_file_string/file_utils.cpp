//
// Created by Scheaven on 2020/9/27.
//

#include "file_utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
#include <stdint.h>
#include <vector>
#include <thread>
#include<iostream>

vector<cv::String> read_images_in_folder(cv::String pattern)
{
    vector<cv::String> fn;
    glob(pattern, fn, false);

    return fn;
}

bool fileExists(const std::string& fileName)
{
    std::fstream file;
    file.open(fileName.c_str(), std::ios::in);
    if (file.is_open() == true)
    {
        file.close();
        return true;
    }
    file.close();
    return false;
}

static void copyFile(const std::string& fileNameFrom, const std::string& fileNameTo)
{
    assert(fileExists(fileNameFrom));

    std::cout <<fileNameFrom << " : "<<fileNameTo<< endl;

    std::ifstream in (fileNameFrom.c_str());
    std::ofstream out (fileNameTo.c_str());
    out << in.rdbuf();
    out.close();
    in.close();
}

void globFile(string path, std::vector<string> res_vec)
{
    printf("------------%s\n", "ioio");
}

int main(int argc, char const *argv[])
{
    /* code */
    string path="/data/disk2/01_dataset/03_human/02_person/";
    std::vector<string> video_path_vec;
    globFile(path, video_path_vec);
    return 0;
}
