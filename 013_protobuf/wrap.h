#ifndef _c_wrap_libprotobuf_3_11_2_h_
#define _c_wrap_libprotobuf_3_11_2_h_ 


#ifdef __cplusplus
extern "C"{
#endif

#include <stddef.h>
#include <stdint.h>

void c_wrap_protobuf_verify_version();
void c_wrap_protobuf_shutdown_library();

void* c_wrap_protobuf_image_unmarshal(void *data, const size_t size);
void c_wrap_protobuf_image_release(void *img);
unsigned char *c_wrap_protobuf_image_get(void *img, int *w, int *h, int *c);
int c_wrap_protobuf_image_get_all_info(void *img, unsigned char **img_data, int *img_w, int *img_h, int *img_c,
    char **cid, char **cname, char **stamp, int64_t *img_id);

void* c_wrap_protobuf_rulemsg_unmarshal(void *data, const size_t size);
void* c_wrap_protobuf_rulemsg_add_sdkmsg(void *rmsg, const char* dtype, const char *sdktype, 
    const char *sdkid, const char *sdkname, const char *stamp);
int c_wrap_protobuf_sdkmsg_add_target(void *smsg, const uint64_t *id, const int confidence,
    const int l, const int t, const int r, const int b, 
    const char *feat, const int feat_size, const char *attr, const int attr_size);
int c_wrap_protobuf_rulemsg_release_and_update(void *rmsg, void *data);


int c_wrap_protobuf_last_sdkmsg_targets_count(void *rmsg);
int c_wrap_protobuf_last_sdkmsg_targets_get(void *rmsg, const int index,
    int *l, int *t, int *r, int *b, int *confidence);

#ifdef __cplusplus
}
#endif

#endif