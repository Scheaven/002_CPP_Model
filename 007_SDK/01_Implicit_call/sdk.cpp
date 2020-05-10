#include "sdk.h"

#include <stdio.h>
#include <dlfcn.h>
#include <sys/shm.h>
#include <time.h>

#ifdef __cplusplus //
extern "C"
{
#endif
#include "std_target.h"

// sdk interface func name
// sdk-interface-name
const static char sin_create[]          = "create";
const static char sin_release[]         = "release";
const static char sin_get_result[]      = "get_result";
const static char sin_release_result[]  = "release_result";

#define check(lib, fn, log, lib_name, fn_name, ret) do{ \
    if (!fn){ \
        dlclose(lib); \
        lib=NULL; \
        printf("dlsym func \"%s\" from file \"%s\" failed", fn_name, lib_name); \
        return ret; \
    } \
}while(0)

namespace container
{
    sdk::sdk(const char *id)
    :libsdk_(nullptr)
    ,sdk_handle_(nullptr)
    ,fn_create(nullptr)
    ,fn_release(nullptr)
    ,fn_get_result(nullptr)
    ,fn_release_result(nullptr)
    ,id_or_name_(id)
    {}
    
    sdk::~sdk()
    {
        release();
    }
    
    int sdk::release(){

        if (sdk_handle_ && fn_release){
            fn_release(sdk_handle_);
        }
        if (libsdk_){
            dlclose(libsdk_);
            libsdk_ = NULL;
        }

        return 0;
    }
 
    int sdk::init(const char *so, const char *conf){
        if (libsdk_) return 0;

        libsdk_ = dlopen(so, RTLD_LAZY);
        if (!libsdk_) {
            printf("sdk dlopen %s conf %s error %s\n", so, conf, dlerror());
            return -1;
        }

        // MUST EXIST FUNCTIONS
        fn_create = (fn_sdk_create)dlsym(libsdk_, sin_create);
        check(libsdk_, fn_create, fn_log_, so, sin_create, -1);
        

        fn_release = (fn_sdk_release)dlsym(libsdk_, sin_release);
        check(libsdk_, fn_release, fn_log_, so, sin_release, -1);
        
        fn_get_result = (fn_sdk_get_result)dlsym(libsdk_, sin_get_result);
        check(libsdk_, fn_get_result, fn_log_, so, sin_get_result, -1);

        fn_release_result = (fn_sdk_release_result)dlsym(libsdk_, sin_release_result);
        check(libsdk_, fn_release_result, fn_log_, so, sin_release_result, -1);

        int max_chan = 7;
        if ((sdk_handle_ = fn_create(conf, &max_chan)) == NULL){
            printf("sdk create sdk handle failed");
            return -1;
        }
        if (max_chan <= 0) max_chan = 16;
        return 0;
    }

    int sdk::run(void *pic_data, int w, int h, int chn) {

        TImage img;
        img.width = w;
        img.height = h;
        img.channel = chn;
        img.data = (unsigned char *)pic_data;

        void * sr = fn_get_result(sdk_handle_, &img, 0);
        TResult * t_result = (TResult*) sr;

       // printf("t_result->count==%d\n", t_result->count);
       // for (int i = 0; i <t_result->count ; ++i) {
       //     printf("=======id:%d confidence:%d left:%d top:%d \n",t_result->targets[i].id,t_result->targets[i].confidence , t_result->targets[i].rect.left, t_result->targets[i].rect.top );
       // }

        fn_release_result(sr);
        //free(img);
        return 1;
    }


} // namespace container
#ifdef __cplusplus //
}
#endif
