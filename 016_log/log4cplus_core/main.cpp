#include "log4plus_util.h"
#include <boost/format.hpp>

int main()
{
    CLog::Initialize("./log4cplus.properties");
    for (;;)
    {
        DEBUG((boost::format("%s:%d, %s:%f, %s:%d, %s:%d") %"id:" %1 %"conf:" %2.5 %", to tmpbox y:" %100 %", tmpbox(3) h:" %200).str());
        DEBUG("Hello, World!");
        WARN("Hello, World!");
        ERROR("Hello, World!");
    }
    return 0;
}
