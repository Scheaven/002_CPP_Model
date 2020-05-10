//
// Created by Scheaven on 2020/4/26.
//

#ifndef H_INTERFACE_H
#define H_INTERFACE_H

#ifdef __cplusplus
extern "C"{
#endif

#define YOLOTRACK_API extern "C" __attribute__((visibility ("default")))

YOLOTRACK_API void* create(const char *conf, int *max_chan);
YOLOTRACK_API void release(void* handle);
YOLOTRACK_API void* get_result(void *handle, const void *img, const int chan);
YOLOTRACK_API void release_result(void *res);

#ifdef __cplusplus
}
#endif
#endif //INC_01_CPP_SORT_HUMAN_INTERFACE_H
