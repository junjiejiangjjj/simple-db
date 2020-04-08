#include "record.h"
#include "simple_db/common/string_util.h"
BEGIN_SIMPLE_DB_NS(db)

Record::Record(const std::string &key, const std::string &value, RecordType recordType):mKey(key),
    mValue(value),
    mRecordType(recordType)
{
}

Record::Record(const char* key, uint32_t size)
{
    if (size == 0) {
        mKey = "";
    } else {
        mKey = std::string(key, size);
    }
    mValue = "";
    mRecordType = RecordType::VALUE;
}

Record::~Record()
{
}

bool Record::GetStringData(const std::string &srcData, uint32_t start, std::string *retStr)
{
    uint32_t size = 10; // key/values record中长度均用10个字符串记录
    if (srcData.size() - size < start) {
        return false;
    }
    uint32_t dataSize = 0;
    if (!StringUtil::StringToUInt32(std::string(srcData, start, size), &dataSize)) {
        return false;
    }
    start += size;
    size = dataSize;
    if (srcData.size() - size < start) {
        return false;
    }    
    *retStr = std::string(srcData, start, dataSize);
    return true;
}

bool Record::PaserFromString(const std::string &str)
{
    // get key
    size_t start = 0;
    if (!GetStringData(str, start, &mKey)) {
        LOG_ERROR << "Get key failed: " << str;
        return false;
    }

    // get tag
    start = 10 + mKey.size();
    uint32_t nextSize = 8;
    if (str.size() - nextSize < start) {
        LOG_ERROR << "Error record: " << str;
        return false;
    }    
    uint32_t tag = 0;
    if (!StringUtil::StringToUInt32(std::string(str, start, nextSize), &tag)) {
        LOG_ERROR << "Paser key size failed: " << str;
        return false;
    }
    if (tag == 0) {
        mRecordType = RecordType::VALUE;
    } else {
        mRecordType = RecordType::DELETE;        
    }
    

    // get values
    start += nextSize;
    nextSize = 10;
    if (!GetStringData(str, start, &mValue)) {
        LOG_ERROR << "Get value failed: " << str;
        return false;
    }
    return true;
}

bool Record::PaserFromSlice(const util::Slice &str)
{
    std::string s(str.GetData(), str.GetSize());
    return PaserFromString(s);
}

void Record::SerializeToString(std::string *str) const
{
    // {key_size}{user_key}{tag}{value_size}{value}
    //    10 + len(user_key) + 8 + 10 + len(value)
    std::string keySizeStr = StringUtil::UInt32ToString(mKey.size(), 10);
    std::string tagStr = StringUtil::UInt32ToString(mRecordType, 8);
    std::string valueSizeStr = StringUtil::UInt32ToString(mValue.size(), 10);
    *str = keySizeStr + mKey + tagStr + valueSizeStr + mValue;
}

END_SIMPLE_DB_NS(db)

