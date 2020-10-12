//
// Created by Scheaven on 2020/9/9.
//

#include "log_util.h"
#include "../easylogging++.h"
INITIALIZE_EASYLOGGINGPP

SLOG* SLOG::instance = NULL;
SLOG* SLOG::getInstance()
{
    if(SLOG::instance==NULL){
        instance = new SLOG();
    }
    return instance;
}

SLOG::SLOG()
{
    el::Loggers::configureFromGlobal("../lib/my_log.conf");
}

SLOG::~SLOG()
{

}

void SLOG::release()
{
    delete SLOG::instance;
    SLOG::instance = NULL;
}

void SLOG::addLog(int type, std::string context)
{
    switch(type)
    {
        case 0:
            LOG(INFO) << context;
            break;
        case 1:
            LOG(WARNING) << context;
            break;
        case 2:
            LOG(ERROR) << context;
            break;
        case 3:
            LOG(DEBUG) << context;
            break;
        case 4:
            LOG(TRACE) << context;
            break;
    }
}