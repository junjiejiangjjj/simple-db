#include "simple_db/common/string_util.h"
#include <sstream>
#include <iomanip>


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


    std::string StringUtil::UInt32ToString(uint32_t value, size_t outputSize)
    {
        std::ostringstream ostr;
        ostr << std::setw(outputSize) << std::setfill('0') << value;
        return ostr.str();
    }


    bool StringUtil::StringToUInt32(const std::string &strValue, uint32_t *value)
    {
        try {
            (*value) = std::stoul(strValue);
        } catch (std::invalid_argument){
            return false;
        } catch (std::out_of_range) {
            return false;
        }
        return true;
    }

}

