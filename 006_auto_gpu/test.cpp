#include "nvidia_gpu_util.h"

int main(int argc, char const *argv[])
{
    /* code */
    int gpu_device = gpu::nv_get_suitable_gpu();
    printf("%d\n",gpu_device);
    return 0;
}
