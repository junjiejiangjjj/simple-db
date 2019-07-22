#ifndef SIMPLE_DB_STRING_UTIL_H
#define SIMPLE_DB_STRING_UTIL_H

#include "simple_db/common/common.h" 

BEGIN_SIMPLE_DB_NS(util)

class StringUtil {
private:
    StringUtil() = delete;
    ~StringUtil() = delete;
    StringUtil(const StringUtil&) = delete;
    StringUtil& operator=(const StringUtil&) = delete;

public:
    static std::string GetLatestName(const std::string& name);
    static std::string GetLatestName(const char* name);
    static std::string GetTimeString(const std::string& timeFormat);
};

END_SIMPLE_DB_NS(util)

#endif
