#ifndef SIMPLE_DB_STRING_UTIL_H
#define SIMPLE_DB_STRING_UTIL_H

#include "simple_db/common/common.h"
#include <string>

namespace simple_db {
    
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
    static std::string UInt32ToString(uint32_t value, size_t outputSize);
    static bool StringToUInt32(const std::string &strValue, uint32_t *value);
};

}

#endif
