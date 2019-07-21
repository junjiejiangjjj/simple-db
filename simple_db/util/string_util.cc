#include "string_util.h"

BEGIN_SIMPLE_DB_NS(util)

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

END_SIMPLE_DB_NS(util)

