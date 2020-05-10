// Opt.cpp
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
// CPP 命令行参数是设置

// 短参数测试案例
void testGetOpt(int argc, char *argv[]) {
    // 短参数的设计实现方法
    int opt;  // getopt() 的返回值
    const char *optstring = "a:b:c:d"; // 设置短参数类型及是否需要参数

    while ((opt = getopt(argc, argv, optstring)) != -1) {
        printf("opt = %c\n", opt);  // 命令参数，亦即 -a -b -c -d
        printf("optarg = %s\n", optarg); // 参数内容
        printf("optind = %d\n", optind); // 下一个被处理的下标值
        printf("argv[optind - 1] = %s\n\n",  argv[optind - 1]); // 参数内容
    }

}

//长参数设置
void getLongOpt(int argc, char *argv[])
{
    static struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"file", required_argument, NULL, 'f'},
        {"output", optional_argument, NULL, 'o'},
        {0, 0, 0, 0}
    };
    static char* const short_options=(char *)"hf:o::";

    int option_index = 0;
    int ret=0;
    while((ret=getopt_long(argc,argv,short_options,long_options,&option_index))!=-1)
    {
        switch(ret)
        {
            case 'h':
                printf("HAVE option: -h\n");   
                break;
            case 'f':
                printf("HAVE option: -f\n"); 
                printf("The argument of -f is %s\n\n",optarg);
                break;
            case 'o':
                printf("HAVE option: -c\n");
                printf("The argument of -c is %s\n\n",optarg);
                break;
            case '?':
                break;
        }
    }
}

int main(int argc, char *argv[]) {
    // testGetOpt(argc, argv);
    getLongOpt(argc, argv);
    return 0;
}
