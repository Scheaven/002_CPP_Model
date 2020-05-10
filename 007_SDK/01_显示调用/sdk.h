#ifndef _c_container_sdk_h_
#define _c_container_sdk_h_

#ifdef __cplusplus //
extern "C"
{
#endif

typedef void* (*fn_sdk_create)(const char*, int*);
typedef void (*fn_sdk_release)(void*);
typedef void* (*fn_sdk_get_result)(void*, const void*, const int);
typedef void (*fn_sdk_release_result)(void *);

namespace container
{

    class sdk
    {
    private:
        void                            *libsdk_;
        void                            *sdk_handle_;
        fn_sdk_create                   fn_create;
        fn_sdk_release                  fn_release;
        fn_sdk_get_result               fn_get_result;
        fn_sdk_release_result           fn_release_result;

        const char *                     id_or_name_;


    public:
        sdk(const char *id);
        ~sdk();

        int init(const char *so, const char *conf);
        int release();
        int run(void *pic_data, int w, int h, int chn);
    };
    
} // namespace container

#ifdef __cplusplus //
}
#endif
#endif