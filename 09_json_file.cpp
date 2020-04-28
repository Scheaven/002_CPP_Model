//json 需要添加环境文件有以及 创建软连接
#include <json/xxx.h>

///////////////////// ------------------------从字符串中读取json
#include <string>
#include <json/json.h>
#include <iostream>
#include <fstream>
using namespace std;

void readStrJson(); //从字符串中读取JSON
void readStrProJson(); //从字符串中读取JSON（内容复杂些）

int main(int argc, char *argv[]) 
{
    readStrJson();

    cout << "\n\n";
    readStrProJson();

    return 0;
}

//从字符串中读取JSON
void readStrJson() 
{
    //字符串
  const char* str = 
      "{\"praenomen\":\"Gaius\",\"nomen\":\"Julius\",\"cognomen\":\"Caezar\","
      "\"born\":-100,\"died\":-44}";

  /*
  //json内容如下：
  {
        "praenomen":"Gaius",
        "nomen":"Julius",
        "cognomen":"Caezar",
        "born":-100,
        "died":-44 
    }
  */

  Json::Reader reader;
  Json::Value root;

  //从字符串中读取数据
  if(reader.parse(str,root))
  {
      string praenomen = root["praenomen"].asString();
      string nomen = root["nomen"].asString();
      string cognomen = root["cognomen"].asString();
      int born = root["born"].asInt();
      int died = root["died"].asInt();

      cout << praenomen + " " + nomen + " " + cognomen
          << " was born in year " << born 
          << ", died in year " << died << endl;
  }

}

//////////////////// ------------------------从字符串中读取JSON（内容复杂些）
void readStrProJson() 
{
    string strValue = "{\"name\":\"json\",\"array\":[{\"cpp\":\"jsoncpp\"},{\"java\":\"jsoninjava\"},{\"php\":\"support\"}]}";
    /*
    //json内容如下：
    {
    "name": "json″,
    "array": [
        {
            "cpp": "jsoncpp"
        },
        {
            "java": "jsoninjava"
        },
        {
            "php": "support"
        }
    ]
    }
    */


    Json::Reader reader;
    Json::Value value;

    if (reader.parse(strValue, value))
    {
        string out = value["name"].asString();
        cout << out << endl;
        const Json::Value arrayObj = value["array"];
        for (unsigned int i = 0; i < arrayObj.size(); i++)
        {
            if (!arrayObj[i].isMember("cpp")) 
                continue;
            out = arrayObj[i]["cpp"].asString();
            cout << out;
            if (i != (arrayObj.size() - 1))
                cout << endl;
        }
    }
}










///////////////////////// ------------------------从文件中读取JSON
#include <string>
#include <json/json.h>
#include <iostream>
#include <fstream>
using namespace std;

void readFileJson(); //从文件中读取JSON，一个存储了JSON格式字符串的文件

int main(int argc, char *argv[]) 
{
    readFileJson();

    return 0;
}

//从文件中读取JSON
void readFileJson()
{
    Json::Reader reader;
    Json::Value root;

    //从文件中读取，保证当前文件有test.json文件
    ifstream in("test.json", ios::binary);
    //in.open("test.json", ios::binary);

    if( !in.is_open() )  
    { 
    cout << "Error opening file\n"; 
    return; 
    }

    /*
    //test.json内容如下：
    {
        "name":"Tsybius",
        "age":23,
        "sex_is_male":true,
        "partner":
        {
            "partner_name":"Galatea",
            "partner_age":21,
            "partner_sex_is_male":false
        },
        "achievement":["ach1","ach2","ach3"]
    }
    */

    if(reader.parse(in,root))
    {
    //读取根节点信息
    string name = root["name"].asString();
    int age = root["age"].asInt();
    bool sex_is_male = root["sex_is_male"].asBool();

    cout << "My name is " << name << endl;
    cout << "I'm " << age << " years old" << endl;
    cout << "I'm a " << (sex_is_male ? "man" : "woman") << endl;

    //读取子节点信息
    string partner_name = root["partner"]["partner_name"].asString();
    int partner_age = root["partner"]["partner_age"].asInt();
    bool partner_sex_is_male = root["partner"]["partner_sex_is_male"].asBool();

    cout << "My partner's name is " << partner_name << endl;
    cout << (partner_sex_is_male ? "he" : "she") << " is "
        << partner_age << " years old" << endl;

    //读取数组信息
    cout << "Here's my achievements:" << endl;
    for(unsigned int i = 0; i < root["achievement"].size(); i++)
    {
        string ach = root["achievement"][i].asString();
        cout << ach << '\t';
    }
    cout << endl;

    cout << "Reading Complete!" << endl;
    }
    else
    {
    cout << "parse error\n" << endl;    
    }

    in.close();
}

test.json文件内容如下:
{
    "name":"Mike Jiang",
    "age":23,
    "sex_is_male":true,
    "partner":
    {
        "partner_name":"Galatea",
        "partner_age":21,
        "partner_sex_is_male":false
    },
    "achievement":["ach1","ach2","ach3"]
}













//////////////////////////// ------------------------把信息保存为JSON格式
#include <string>
#include <json/json.h>
#include <iostream>
#include <fstream>
using namespace std;

void writeFileJson();//将信息保存为JSON格式

int main(int argc, char *argv[]) 
{
    writeFileJson();

    return 0;
}

//将信息保存为JSON格式
void writeFileJson()
{
    //根节点
    Json::Value root;

    //根节点属性
    root["name"] = Json::Value("Mike Jiang");
    root["age"] = Json::Value(23);
    root["sex_is_male"] = Json::Value(true);

    //子节点
    Json::Value partner;

    //子节点属性
    partner["partner_name"] = Json::Value("Galatea");
    partner["partner_age"] = Json::Value(21);
    partner["partner_sex_is_male"] = Json::Value(false);

    //子节点挂到根节点上
    root["partner"] = Json::Value(partner);

    //数组形式
    root["achievement"].append("ach1");
    root["achievement"].append("ach2");
    root["achievement"].append("ach3");

    //直接输出
    cout << "FastWriter:" << endl;
    Json::FastWriter fw;
    cout << fw.write(root) << endl << endl;

    //缩进输出
    cout << "StyledWriter:" << endl;
    Json::StyledWriter sw;
    cout << sw.write(root) << endl << endl;

    //输出到文件
    ofstream os;
    os.open("demo.json");
    os << sw.write(root);
    os.close();

    /*
    //json文件内容如下：
    {
        "achievement" : [ "ach1", "ach2", "ach3" ],
        "age" : 23,
        "name" : "Mike Jiang",
        "partner" : {
            "partner_age" : 21,
            "partner_name" : "Galatea",
            "partner_sex_is_male" : false
        },
        "sex_is_male" : true
    }
    */

}