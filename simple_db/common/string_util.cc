#include "simple_db/common/string_util.h"


namespace simple_db {
    

std::string StringUtil::GetLatestName(const std::string& name)
{
    auto pos = name.rfind('/');
    if (pos == std::string::npos) {
        return name;
    } else {
        return name.substr(pos+1, name.size());
    }
}

std::string StringUtil::GetLatestName(const char* name)
{
    std::string s(name);
    return GetLatestName(s);
}

std::string StringUtil::GetTimeString(const std::string& timeFormat)
{
    time_t curTime;
    time(&curTime);
    struct tm t;

    ::localtime_r(&curTime, &t);
    char buf[50];
    ::strftime(buf, 50, timeFormat.c_str(), &t);
    return std::string(buf);
}

}

