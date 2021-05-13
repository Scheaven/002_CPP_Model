#include "log.h"

int main()
{
    CLog::Initialize("./log4cplus.properties");
    DEBUG("Hello, World!");
    WARN("Hello, World!");
    ERROR("Hello, World!");

    return 0;
}

