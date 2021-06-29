#ifndef _LOG4PLUS_UTIL_H_
#define _LOG4PLUS_UTIL_H_

#include <string>
#include <iostream>

#define PLUS_DEBUG(input, ...) PLUS_DEBUG_LOG(__FILE__, __LINE__, input, ##__VA_ARGS__)
#define DEBUG(input) DEBUG_LOG((input), (__FILE__), (__LINE__));
#define ERROR(input) ERROR_LOG((input), (__FILE__), (__LINE__));
#define WARN(input) WARN_LOG((input), (__FILE__), (__LINE__));

using namespace std;
// using namespace log4cplus;

void PLUS_DEBUG_LOG(const std::string& strFile, int iLine, int count, ...);
void DEBUG_LOG(const std::string& strInfo, const std::string& strFile, int iLine);
void ERROR_LOG(const std::string& strInfo, const std::string& strFile, int iLine);
void WARN_LOG(const std::string& strInfo, const std::string& strFile, int iLine);

class CLog
{
public:
    static CLog* Initialize(const std::string& strLogFile);

private:
    CLog(const std::string& strLogFile);
    static CLog* pInstance;
};

#endif
