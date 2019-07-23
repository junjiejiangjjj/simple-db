#ifndef SIMPLE_DB_LOGGING_H
#define SIMPLE_DB_LOGGING_H

#include "simple_db/common/common.h"
#include <sstream>

BEGIN_SIMPLE_DB_NS(util)

class Logging {
public:
    enum LogLevel {
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL,
        NUM_LOG_LEVELS,
    };


public:
    Logging(const char* filename, int line, Logging::LogLevel, const char* func);
    ~Logging();
private:
    Logging(const Logging&);
    Logging& operator=(const Logging&);

public:
    static LogLevel GetLogLevel();
    static void SetLogLevel(LogLevel level);
    std::stringstream& GetStream() {return mSs;}

    typedef void (*OutputFunc)(const char* msg, int len);
    typedef void (*FlushFunc)();
    static void SetOutPut(OutputFunc);
    static void SetFlush(FlushFunc);

public:
    static LogLevel gLogLevel;
    static OutputFunc gOutput;
    static FlushFunc gFlush;


private:

    LogLevel mLevel;
    std::stringstream mSs;
};


inline Logging::LogLevel Logging::GetLogLevel()
{
    return gLogLevel;
}

#define LOG_DEBUG if (Logging::GetLogLevel() <= Logging::DEBUG) \
    Logging(__FILE__, __LINE__, Logging::DEBUG, __func__).GetStream()
#define LOG_INFO if (Logging::GetLogLevel() <= Logging::INFO) \
    Logging(__FILE__, __LINE__, Logging::INFO, __func__).GetStream()
#define LOG_WARN Logging(__FILE__, __LINE__, Logging::WARN, __func__).GetStream()
#define LOG_ERROR Logging(__FILE__, __LINE__, Logging::ERROR, __func__).GetStream()

END_SIMPLE_DB_NS(util)

#endif
