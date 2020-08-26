#include<iostream> 
#include<vector> 
#include<algorithm>
using namespace std; 
typedef struct Bbox 
{
 int x; 
 int y; 
 int w; 
 int h; 
 float score; 
 }Bbox; 
 bool sort_score(Bbox box1,Bbox box2) 
 { 
    return (box1.score > box2.score); 
 } 
 float iou(Bbox box1,Bbox box2) 
 { 
  int x1 = std::max(box1.x,box2.x); 
  int y1 = std::max(box1.y,box2.y); 
  int x2 = std::min((box1.x + box1.w),
  (box2.x + box2.w)); 
  int y2 = std::min((box1.y + box1.h),(box2.y + box2.h)); 
  float over_area = (x2 - x1) * (y2 - y1);
  float iou = over_area/(box1.w * box1.h + box2.w * box2.h-over_area); 
  return iou; 
  } 
  //方法1 
  vector<Bbox> nms(std::vector<Bbox>&vec_boxs,float threshold)
   { 
   std::sort(vec_boxs.begin(),vec_boxs.end(),sort_score); 
   std::vector<Bbox>del(vec_boxs.size(),false); 
   for(int i =0; i<vec_boxs.size();i++) 
   { 
     for (int j =0;j<vec_boxs.size();j++) 
     { 
       float iou_value =iou(vec_boxs[i],vec_boxs[j]); 
       if(iou_value>threshold) 
       { 
         del[j]=true; 
       } 
     } 
   } 
   std::vector<Bbox>results;
    for(const auto i :del)
     { 
     if(!del[i]) results.push_back(vec_box[i]); 
     }
      return results;
       } 
//方法2  这种执行效率更高 
vector<Bbox> nms(std::vector<Bbox>&vec_boxs,float threshold) 
{ 
   vector<Bbox>results; 
   while(vec_boxs.size() > 0) 
   { 
    std::sort(vec_boxs.begin(),vec_boxs.end(),sort_score);        
    results.push_back(vec_boxs[0]); 
    for(int i =0;i <vec_boxs.size()-1;i++)  // 我这边测试需要使用迭代器的方法，因为擦除需要使用写迭代器  迭代器用的是指针，取到数据要加*
    { 
       float iou_value =iou(vec_boxs[0],vec_boxs[i+1]); 
       if (iou_value >threshold) 
       { 
       vec_boxs.erase(vec_boxs[i+1]);  
        } 
    } 
    vec_boxs.erase(vec_boxs[0]);
   } 
} 

---------------------------------
//自己修改好的版本


new
    //NMS 去掉重叠的框信息  start
    std::vector<bbox_t> n_boxes;
    float threshold = 0.8;
    // 需要使用迭代器的方式进行擦除
    for (vector<bbox_t>::iterator it = boxes.begin();it !=boxes.end();)
    {
        if(it->obj_id!=0 && it->obj_id!= 1 && it->obj_id!= 2)
        {
            n_boxes.push_back(*it);
            it = boxes.erase(it);
        }else
            ++it;
    }

    while(boxes.size()>0)
    {
        std::sort(boxes.begin(),boxes.end(),[](bbox_t box1, bbox_t box2){
            return box1.prob>box2.prob;
        });
        n_boxes.push_back(boxes[0]);

        for (vector<bbox_t>::iterator it = boxes.begin()+1;it !=(boxes.end());)
        {
            float iou_value = box_iou(*boxes.begin(),*it);
            if(iou_value>threshold)
            {
                it = boxes.erase(it);
            }
            else
                it++;
        }
        boxes.erase(boxes.begin());
    }


    //NMS 去掉重叠的框信息  end

//NMS 去掉重叠的框信息  start
std::vector<bbox_t> n_boxes;
float threshold = 0.8;
// 需要使用迭代器的方式进行擦除
for (vector<bbox_t>::iterator it = boxes.begin();it !=boxes.end();)
{
    if(it->obj_id!=0 && it->obj_id!= 1 && it->obj_id!= 2)
    {
        n_boxes.push_back(*it);
        it = boxes.erase(it);
    }else
        ++it;
}

while(boxes.size()>0)
{
    std::sort(boxes.begin(),boxes.end(),[](bbox_t box1, bbox_t box2){
        return box1.prob>box2.prob;
    });
    n_boxes.push_back(boxes[0]);

    for (vector<bbox_t>::iterator it = boxes.begin()+1;it !=(boxes.end());)
    {
        float iou_value = box_iou(*boxes.begin(),*it);
        if(iou_value>threshold)
        {
            it = boxes.erase(it);
        }
        else
            it++;
    }
    boxes.erase(boxes.begin());
}


//NMS 去掉重叠的框信息  end