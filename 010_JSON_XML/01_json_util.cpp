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


void readStrProJson()
{
	string strValue = "{\"name\":\"shuiyixin\",\"major\":[{\"AI\":\"MachineLearning\"},{\"AI\":\"DeepLearning\"},{\"AI\":\"ComputerVision\"}]}";
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(strValue, value))
	{
		string out = value["name"].asString();
		cout << out << endl;
		const Json::Value arrayObj = value["major"];
		for (unsigned int i = 0; i < arrayObj.size(); i++)
		{
			out = arrayObj[i]["AI"].asString();
			cout << out<<endl;
		}
	}
}
