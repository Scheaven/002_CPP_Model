//
// Created by Scheaven on 2020/5/14.
//

#ifndef DEMO_TIME_UTIL_H
#define DEMO_TIME_UTIL_H

#include <sys/time.h>

int get_run_time(struct timeval *result, struct timeval *begin, struct timeval *end);

time_t strTime2unix(char* timeStamp);

int char_2_unix(char* str1);

char* fa_getSysTime();

#endif //DEMO_TIME_UTIL_H
