#include "simple_db/util/logging.h"
#include "simple_db/util/string_util.h"
#include <stdio.h>
#include <thread>

BEGIN_SIMPLE_DB_NS(util)

const char* LogLevelNames[Logging::NUM_LOG_LEVELS] =
{
 "TRACE",
 "DEBUG",
 "INFO",
 "WARN",
 "ERROR"
};

void DefaultOutput(const char* msg, int len)
{
    size_t n = ::fwrite(msg, 1, len, stdout);
    (void)n;
}

void DefaultFlush()
{
    ::fflush(stdout);
}

Logging::LogLevel Logging::gLogLevel = Logging::LogLevel::INFO;
Logging::OutputFunc Logging::gOutput = DefaultOutput;
Logging::FlushFunc Logging::gFlush = DefaultFlush;

Logging::Logging(const char* filename, int line, Logging::LogLevel level, const char* func)
{
    mLevel = level;

    mSs << "[" << StringUtil::GetTimeString("%Y-%m-%d %H:%M:%S") << "]"
        << "[" << LogLevelNames[gLogLevel] << "]"
        << "[]" << std::this_thread::get_id() << "]"
        << "[" <<  StringUtil::GetLatestName(filename) << ":" << line << " " << func << "()] ";
}

Logging::~Logging()
{
    mSs << "\n";
    gOutput(mSs.str().c_str(), mSs.str().size());
    gFlush();
}


void Logging::SetLogLevel(Logging::LogLevel level)
{
    gLogLevel = level;
}

void Logging::SetOutPut(OutputFunc out)
{
    gOutput = out;
}

void Logging::SetFlush(FlushFunc flush)
{
    gFlush = flush;
}

END_SIMPLE_DB_NS(util)
