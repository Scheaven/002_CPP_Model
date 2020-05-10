//
// Created by Scheaven on 2020/1/3.
//

#include "reid_feature.h"
#include <cuda_runtime_api.h>
#include <torch/torch.h>

// 抽取图片特征
unsigned char * Feature_extractor_2byte(unsigned char *pBuf, float *pFeature)
{

//    cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
//    image.convertTo(image, CV_32FC3, 1.0f / 255.0f);
    auto input_tensor = torch::from_blob(pBuf, {1, 256, 128, 3});
    input_tensor = input_tensor.permute({0, 3, 1, 2});
    input_tensor[0][0] = input_tensor[0][0].sub_(0.485).div_(0.229);
    input_tensor[0][1] = input_tensor[0][1].sub_(0.456).div_(0.224);
    input_tensor[0][2] = input_tensor[0][2].sub_(0.406).div_(0.225);
    if(this->is_gpu)
        input_tensor = input_tensor.to(at::kCUDA);

    torch::Tensor human_feat =this->module.forward({input_tensor}).toTensor();


    //转化成cpu上的torch才能转化为float
    torch::Tensor query_feat = human_feat.cpu();
    cout << "-----------" <<query_feat[0][0] << endl;

    //torch才能转化为float
    auto foo_one = query_feat.accessor<float,2>();

    ReID_Utils RET;

    unsigned char pFeature[2048][sizeof(f_size)];

    /* 将float的tensor转化成byte流*/
    float f_size = -0.727412;
    for (int64_t i = 0; i < foo_one.size(0); i++) {
        auto a1 = foo_one[i];
        for (int64_t j = 0; j < a1.size(0); j++) {
          cout<< a1[j] << endl;
          unsigned char *single_p = RET.T2bytes<float>(a1[j]);
           cout<< "j::" << j << endl;
           unsigned char *single_p = RET.T2bytes(a1[j]);
           memcpy(pFeature[j], single_p, sizeof(f_size));
            
        }
    }

    //将byte流转化成float后使用
   unsigned char *byte_f = new unsigned char[sizeof(f_size)];
   memcpy(byte_f, pFeature[0], sizeof(f_size));

   f_val = RET.bytes2T<float>(byte_f);
   cout << "---- end okok-------" << RET.bytes2T(byte_f) << endl;

   cout << "---- end 11-------" << pFeature[0] << endl;
   delete []byte_f; //释放内存空间
   return re_f;
}

