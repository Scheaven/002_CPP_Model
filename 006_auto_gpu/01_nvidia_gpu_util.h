#ifndef _nvidia_gpu_util_h_
#define _nvidia_gpu_util_h_
 
namespace gpu{
    int getIdleGPU(const int need);
    char *getGpuInfo();
}
 
#endif