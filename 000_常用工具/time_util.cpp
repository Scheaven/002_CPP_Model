//
// Created by Scheaven on 2020/5/14.
//
#include "time_util.h"
#include <stdio.h>
#include <memory.h>
#include <iostream>
#include <ctime>
#include <string>
#include "stdlib.h"

#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int get_run_time(struct timeval *result, struct timeval *begin, struct timeval * end)
{
    if(begin->tv_sec > end->tv_sec)  return -1;
    if((begin->tv_sec == end->tv_sec) && (begin->tv_usec > end->tv_usec))  return -2;
    result->tv_sec = end->tv_sec - begin->tv_sec;
    result->tv_usec = end->tv_usec - begin->tv_usec;

    if(result->tv_usec<0)
    {
        result->tv_sec--;
        result->tv_usec += 1000000;
    }
    return 0;
}

time_t strTime2unix(char* timeStamp)
{
    struct tm tm;
    memset(&tm, 0, sizeof(tm));

    sscanf(timeStamp, "%d-%d-%d %d:%d:%d",
           &tm.tm_year, &tm.tm_mon, &tm.tm_mday,
           &tm.tm_hour, &tm.tm_min, &tm.tm_sec);

    tm.tm_year -= 1900;
    tm.tm_mon--;

    return mktime(&tm);
}

int char_2_unix(char* str1)
{
    char str[100];
    std::cout<< "==char_2_unix=%s：" << str1 << std::endl;
    strcpy(str, str1);
    const char *mySplit = ".";
    char *p;
    char *p1;
    char *p2;

    p1 = strtok(str, mySplit);
    p2 = strtok(NULL, mySplit);
    time_t t = strTime2unix(p1);

    return t+atoi(p2);
}


char* fa_getSysTime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    struct tm* pTime;
    pTime = localtime(&tv.tv_sec);

    static char sTemp[30] = "0";
    snprintf(sTemp, sizeof(sTemp), "%04d-%02d-%02d %02d:%02d:%02d.%03d", pTime->tm_year+1900, \
            pTime->tm_mon+1, pTime->tm_mday, pTime->tm_hour, pTime->tm_min, pTime->tm_sec, \
            tv.tv_usec/1000);
    char* TP = sTemp;
    return TP;
}

//int main()
//{
//    std::cout<< "当前时间：" << fa_getSysTime() << std::endl;
//    return 0;
//}


int main()
{
    int a = char_2_unix(fa_getSysTime());
    std::cout << a << std::endl;

    return 0;
}