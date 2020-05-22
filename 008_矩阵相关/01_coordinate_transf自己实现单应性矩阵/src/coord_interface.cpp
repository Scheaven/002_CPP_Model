//
// Created by Scheaven on 2020/5/20.
//

#include "coord_interface.h"
#include "switcher_util.h"

CoordSwitcher switcher;
CoordManager::CoordManager(const char *json_document)
{

}

CoordManager::CoordManager(CamVec *CV_Reg)
{
    this->CV_Reg = CV_Reg;
    switcher.initHomography(CV_Reg);
//    this->init_flag = false;
//    CoordSwitcher switcher(CV_Reg);

}

CoordManager::~CoordManager() {}

float confidence =0.0;
map<string,float> CoordManager::group_compare(MatchHuman *A_Human, MatchHuman *B_Human)
{
    map<string,float> confidence_map;
    for (int i = 0; i < A_Human->count; ++i) {
        for (int j = 0; j < B_Human->count; ++j) {
            confidence = switcher.compare(A_Human->humanInfo[i].point, B_Human->humanInfo[j].point);
            confidence_map.insert(pair<string,float >(to_string(A_Human->humanInfo[i].human_id)+ ":" +to_string(B_Human->humanInfo[j].human_id), confidence));
        }
    }
    return confidence_map;
}