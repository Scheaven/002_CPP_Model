//
// Created by Scheaven on 2020/9/9.
//

#ifndef LOG_UTIL_H
#define LOG_UTIL_H

#include "../config.h"

class SLOG{
public:
    static SLOG* instance;
    static SLOG* getInstance();

    SLOG();
    ~SLOG();
    void release();

public:
    void addLog(int type, std::string context);
};

#endif //COSINE_METRIC_LEARNING_LOG_UTIL_H_H
