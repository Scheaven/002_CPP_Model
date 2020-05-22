//
// Created by Scheaven on 2020/5/20.
//

#ifndef INC_01_COORDINATE_TRANSFORMATION_COORD_INTERFACE_H
#define INC_01_COORDINATE_TRANSFORMATION_COORD_INTERFACE_H

#include "../con_target.h"

class CoordManager
{
private:
    CamVec *CV_Reg;
    bool init_flag;

public:
    CoordManager(const char* json_document);
    CoordManager(CamVec *CV_Reg);
    ~CoordManager();
    map<string,float > group_compare(MatchHuman * A_Human, MatchHuman * B_Human);
};


#endif //INC_01_COORDINATE_TRANSFORMATION_COORD_INTERFACE_H
