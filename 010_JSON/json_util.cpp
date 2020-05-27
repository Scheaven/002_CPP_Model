//
// Created by Scheaven on 2020/5/26.
//

#include "json_util.h"

string map_json(map<string,float> s_map)
{
    string json = "";
    map<string,float>::iterator iter;
    for (iter= s_map.begin(); iter!= s_map.end();iter++ ) {
        json += "{\"" + iter->first + "\":" + "" +to_string(iter->second) + "},";
    }
    return json;
}

string map_json(map<int,int> s_map)
{
    string json = "";
    map<int,int>::iterator iter;
    for (iter= s_map.begin(); iter!= s_map.end();iter++ ) {
        json += "{\""+ to_string(iter->first) + "\":" + to_string(iter->second) + "},";
    }
    return json;
}
