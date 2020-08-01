//
// Created by Scheaven on 2020/7/28.
//

#include "annotation_utils.h"

void Create_VOCXML(string xml_path, XML_Info* xmlInfo)
{
    TiXmlDocument doc;
    TiXmlElement* root = new TiXmlElement("annotation");
    doc.LinkEndChild(root);

    TiXmlElement* folder = new TiXmlElement("folder");
    root->LinkEndChild(folder);

    TiXmlText* train = new TiXmlText("train");
    folder->LinkEndChild(train);

    TiXmlElement* filename = new TiXmlElement("filename");
    root->LinkEndChild(filename);

    TiXmlText* fileName_d = new TiXmlText(xmlInfo->fileName);
    filename->LinkEndChild(fileName_d);

    TiXmlElement* path = new TiXmlElement("path");
    root->LinkEndChild(path);

    TiXmlText* filePath = new TiXmlText(xmlInfo->filePath);
    path->LinkEndChild(filePath);

    TiXmlElement* source = new TiXmlElement("source");
    root->LinkEndChild(source);

    TiXmlElement* database = new TiXmlElement("database");
    source->LinkEndChild(database);

    TiXmlText* auto_create = new TiXmlText("auto create");
    database->LinkEndChild(auto_create);

    //设置img信息
    TiXmlElement* img_size = new TiXmlElement("size");
    root->LinkEndChild(img_size);

    TiXmlElement* img_width = new TiXmlElement("width");
    img_size->LinkEndChild(img_width);

    TiXmlText* img_w = new TiXmlText(to_string(xmlInfo->img_w).c_str());
    img_width->LinkEndChild(img_w);

    TiXmlElement* img_height = new TiXmlElement("height");
    img_size->LinkEndChild(img_height);

    TiXmlText* img_h = new TiXmlText(to_string(xmlInfo->img_h).c_str());
    img_height->LinkEndChild(img_h);

    TiXmlElement* img_depth = new TiXmlElement("depth");
    img_size->LinkEndChild(img_depth);

    TiXmlText* img_d = new TiXmlText(to_string(xmlInfo->img_depth).c_str());
    img_depth->LinkEndChild(img_d);

    //设置img信息
    TiXmlElement* segmented = new TiXmlElement("segmented");
    root->LinkEndChild(segmented);

    TiXmlText* seg_num = new TiXmlText("0"); //是否用于分割
    segmented->LinkEndChild(seg_num);
    try
    {
        // 目标信息
        for (int i = 0; i < xmlInfo->box_count; ++i)
        {
            if(xmlInfo->boxInfo[i].prob>0.6)
            {
                //设置img信息
                TiXmlElement* object = new TiXmlElement("object");
                root->LinkEndChild(object);

                TiXmlElement* name = new TiXmlElement("name");
                object->LinkEndChild(name);

                TiXmlText* box_label = new TiXmlText(xmlInfo->boxInfo[i].name);
                name->LinkEndChild(box_label);

                TiXmlElement* pose = new TiXmlElement("pose");
                object->LinkEndChild(pose);

                TiXmlText* Frontal = new TiXmlText("Unspecified"); //拍摄角度 Unspecified未指明
                pose->LinkEndChild(Frontal);


                TiXmlElement* truncated = new TiXmlElement("truncated");
                object->LinkEndChild(truncated);

                TiXmlText* truncated_t = new TiXmlText("0"); // 是否被截断 0表示未被截断
                truncated->LinkEndChild(truncated_t);

//            TiXmlElement* occluded = new TiXmlElement("occluded");
//            object->LinkEndChild(occluded); //是否发生遮挡
//
//            TiXmlText* occluded_t = new TiXmlText("0");
//            occluded->LinkEndChild(occluded_t);

                TiXmlElement* difficult = new TiXmlElement("difficult");
                object->LinkEndChild(difficult);

                TiXmlText* difficult_t = new TiXmlText("0"); // 是否难以识别 0表示容易识别
                difficult->LinkEndChild(difficult_t);

                // bbox信息
                TiXmlElement* bndbox = new TiXmlElement("bndbox");
                object->LinkEndChild(bndbox);

                TiXmlElement* xmin = new TiXmlElement("xmin");
                bndbox->LinkEndChild(xmin);

                TiXmlText* xmin_t = new TiXmlText(to_string(xmlInfo->boxInfo[i].xmin).c_str());
                xmin->LinkEndChild(xmin_t);

                TiXmlElement* ymin = new TiXmlElement("ymin");
                bndbox->LinkEndChild(ymin);

                TiXmlText* ymin_t = new TiXmlText(to_string(xmlInfo->boxInfo[i].ymin).c_str());
                ymin->LinkEndChild(ymin_t);

                TiXmlElement* xmax = new TiXmlElement("xmax");
                bndbox->LinkEndChild(xmax);

                TiXmlText* xmax_t = new TiXmlText(to_string(xmlInfo->boxInfo[i].xmax).c_str());
                xmax->LinkEndChild(xmax_t);

                TiXmlElement* ymax = new TiXmlElement("ymax");
                bndbox->LinkEndChild(ymax);

                TiXmlText* ymax_t = new TiXmlText(to_string(xmlInfo->boxInfo[i].ymax).c_str());
                ymax->LinkEndChild(ymax_t);
            }
        }

        bool succ = doc.SaveFile(xml_path.c_str());
        doc.Clear();
    }catch(exception& e)
    {
        cout << "--error:" << e.what() << endl;
    }
}



/*
添加节点
addposion，从外到添加节点的路径
hierachy，节点的层数，包括子元素
attributes,添加元素
count_attributes，元素个数
flag,为1时，在子节点添加，为2时，在兄弟节点添加
*/
void add_NodeXML(string path, XML_Info* xmlInfo)
{
    TiXmlDocument doc;
    const char* path_add = path.c_str();
    ifstream fin(path);
    if(!fin) return;
//    if (doc.LoadFile(path_add)) return ;
    doc.LoadFile(path_add);
    TiXmlElement *current_root = doc.FirstChildElement("annotation");//翻查主节点
    //    TiXmlDocument *pDocument = new TiXmlDocument(xmlFileName.c_str());
//    if (NULL == pDocument)
//    {
//        return;
//    }
//    pDocument->LoadFile(xmlFileName.c_str());
//
//    TiXmlElement *pRoot = pDocument->RootElement();


    try
    {
        // 目标信息
        for (int i = 0; i < xmlInfo->box_count; ++i)
        {
            if(xmlInfo->boxInfo[i].prob>0.6)
            {
                //设置img信息
                TiXmlElement* object = new TiXmlElement("object");
//                root->LinkEndChild(object);

                TiXmlElement* name = new TiXmlElement("name");
                object->LinkEndChild(name);

                TiXmlText* box_label = new TiXmlText(xmlInfo->boxInfo[i].name);
                name->LinkEndChild(box_label);

                TiXmlElement* pose = new TiXmlElement("pose");
                object->LinkEndChild(pose);

                TiXmlText* Frontal = new TiXmlText("Unspecified"); //拍摄角度 Unspecified未指明
                pose->LinkEndChild(Frontal);


                TiXmlElement* truncated = new TiXmlElement("truncated");
                object->LinkEndChild(truncated);

                TiXmlText* truncated_t = new TiXmlText("0"); // 是否被截断 0表示未被截断
                truncated->LinkEndChild(truncated_t);

//            TiXmlElement* occluded = new TiXmlElement("occluded");
//            object->LinkEndChild(occluded); //是否发生遮挡
//
//            TiXmlText* occluded_t = new TiXmlText("0");
//            occluded->LinkEndChild(occluded_t);

                TiXmlElement* difficult = new TiXmlElement("difficult");
                object->LinkEndChild(difficult);

                TiXmlText* difficult_t = new TiXmlText("0"); // 是否难以识别 0表示容易识别
                difficult->LinkEndChild(difficult_t);

                // bbox信息
                TiXmlElement* bndbox = new TiXmlElement("bndbox");
                object->LinkEndChild(bndbox);

                TiXmlElement* xmin = new TiXmlElement("xmin");
                bndbox->LinkEndChild(xmin);

                TiXmlText* xmin_t = new TiXmlText(to_string(xmlInfo->boxInfo[i].xmin).c_str());
                xmin->LinkEndChild(xmin_t);

                TiXmlElement* ymin = new TiXmlElement("ymin");
                bndbox->LinkEndChild(ymin);

                TiXmlText* ymin_t = new TiXmlText(to_string(xmlInfo->boxInfo[i].ymin).c_str());
                ymin->LinkEndChild(ymin_t);

                TiXmlElement* xmax = new TiXmlElement("xmax");
                bndbox->LinkEndChild(xmax);

                TiXmlText* xmax_t = new TiXmlText(to_string(xmlInfo->boxInfo[i].xmax).c_str());
                xmax->LinkEndChild(xmax_t);

                TiXmlElement* ymax = new TiXmlElement("ymax");
                bndbox->LinkEndChild(ymax);

                TiXmlText* ymax_t = new TiXmlText(to_string(xmlInfo->boxInfo[i].ymax).c_str());
                ymax->LinkEndChild(ymax_t);

                current_root->InsertEndChild(*object);
            }
        }

        doc.SaveFile(path_add);
//        bool succ = doc.SaveFile(xml_path.c_str());
//        doc.Clear();
    }catch(exception& e)
    {
        cout << "--error:" << e.what() << endl;
    }


    return ;
}


//void Insert(const string xmlFileName, const map<string, string> &T_Map)
//{
//    //创建XML文档指针
//    TiXmlDocument *pDocument = new TiXmlDocument(xmlFileName.c_str());
//    if (NULL == pDocument)
//    {
//        return;
//    }
//    pDocument->LoadFile(xmlFileName.c_str());
//
//    TiXmlElement *pRoot = pDocument->RootElement();
//    if (NULL == pRoot)
//    {
//        return;
//    }
//
//    //创建孩子节点
//    string rootName = (xmlFileName.substr(0, xmlFileName.find(".")));//根节点元素名为文件名去掉.xml后+Record
//    rootName += "Record";
//    TiXmlElement *pNode = new TiXmlElement(rootName.c_str());
//    if (NULL == pNode)
//    {
//        return;
//    }
//
//    TiXmlElement *pColumnNode = NULL;
//    TiXmlText    *pColumnText = NULL;
//    for (auto it = T_Map.begin(); it != T_Map.end(); ++it)
//    {
//        pColumnNode = new TiXmlElement(it->first.c_str());
//        pColumnText = new TiXmlText(it->second.c_str());
//        pColumnNode->LinkEndChild(pColumnText);
//        pNode->LinkEndChild(pColumnNode);
//    }
//
//    pRoot->InsertEndChild(*pNode);
//    pDocument->SaveFile(xmlFileName.c_str());
//}


