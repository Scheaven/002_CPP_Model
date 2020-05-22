#include <iostream>
#include "./src/coord_interface.h"
#include "con_target.h"
#include "./src/math_util.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
//    float Ax = 30.0f, Ay = 110.0f, Bx = 326.36f, By = 64.45f;
//    const char* config_str = "{\"leftCam\":{ \"A1x\": 30.0, \"A1y\":110.0 ,\"A2x\": 120.0,\"A2y\":200.0, ,\"A3x\": 80.0,\"A3y\":400.0, ,\"A4x\": 20.0,\"A4y\":287.0},"
//                                "rightCam\":{ \"B1x\": 30.0, \"B1y\":110.0 ,\"B2x\": 120.0,\"B2y\":200.0, ,\"B3x\": 80.0,\"B3y\":400.0, ,\"B4x\": 20.0,\"B4y\":287.0}"
//                                "}";

//    CoordManager CM(config_str);

    // ---- 初始化赋值 ---
    CamVec *CV_Reg = (CamVec*)malloc(sizeof(CamVec));

    int reg_point_size = 4;
    CV_Reg->regInfo = (RegInfo*)malloc(sizeof(RegInfo)*2); // 右侧的点

    SPoint2f *regA_point = (SPoint2f*)malloc(sizeof(SPoint2f)*reg_point_size);
    regA_point[0] = SPoint2f(100.0f, 100.0f);
    regA_point[1] = SPoint2f(120.0f, 200.0f);
    regA_point[2] = SPoint2f(80.0f, 400.0f);
    regA_point[3] = SPoint2f(20.0f, 287.0f);
    CV_Reg->regInfo[0].count = reg_point_size;
    CV_Reg->regInfo[0].point = regA_point;

    SPoint2f* regB_point = (SPoint2f*)malloc(sizeof(SPoint2f)*reg_point_size);
    regB_point[0] = SPoint2f(326.36f, 64.45f);
    regB_point[1] = SPoint2f(339.16f, 128.24f);
    regB_point[2] = SPoint2f(313.73f, 255.86f);
    regB_point[3] = SPoint2f(275.41f, 183.80f);
    CV_Reg->regInfo[1].count = reg_point_size;
    CV_Reg->regInfo[1].point = regB_point;

    CoordManager CM(CV_Reg); //初始化区域信息


    // 获取待匹配的点信息
    MatchHuman * A_Human = (MatchHuman*)malloc(sizeof(MatchHuman));
    int A_hcount = 3;
    A_Human->humanInfo = (HumanInfo*)malloc(sizeof(HumanInfo)*A_hcount);
    A_Human->humanInfo[0].human_id = 1;
    A_Human->humanInfo[0].point = SPoint2f(100.0f, 100.0f);
    A_Human->humanInfo[1].human_id = 2;
    A_Human->humanInfo[1].point = SPoint2f(30.0f, 110.0f);
    A_Human->humanInfo[2].human_id = 3;
    A_Human->humanInfo[2].point = SPoint2f(35.0f, 100.0f);
    A_Human->count = A_hcount;

    MatchHuman * B_Human = (MatchHuman*)malloc(sizeof(MatchHuman));
    int B_hcount = 2;
    B_Human->humanInfo = (HumanInfo*)malloc(sizeof(HumanInfo)*B_hcount);
    B_Human->humanInfo[0].human_id = 3;
    B_Human->humanInfo[0].point = SPoint2f(326.36f, 64.45f);
    B_Human->humanInfo[1].human_id = 5;
    B_Human->humanInfo[1].point = SPoint2f(284.9f, 64.49f);
    B_Human->count = B_hcount;


    // 创建获取结果的结构体


    map<string,float> confidence_map;
    confidence_map = CM.group_compare(A_Human, B_Human);// 批量匹配区域中的人


    //遍历结果
    map<string,float>::iterator iter;
    for (iter=confidence_map.begin() ;iter!=confidence_map.end();iter++) {
        std::cout<< iter->first << "  confidence   " << iter->second << std::endl;
    }


    std::cout << "--over" << std::endl;
    return 0;
}