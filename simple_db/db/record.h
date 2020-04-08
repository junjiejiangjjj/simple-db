#ifndef SIMPLE_DB_RECORD_H
#define SIMPLE_DB_RECORD_H

#include "simple_db/common/common.h"
#include "simple_db/util/slice.h"

BEGIN_SIMPLE_DB_NS(db)

class Record final {
    // table record:
    // {key_size}{user_key}{tag}{value_size}{value}
    //    10 + len(user_key) + 8 + 10 + len(value)

public:
    enum RecordType { VALUE=0, DELETE=1};

public:
    Record(const std::string &key, const std::string &value, RecordType recordType);
    Record() {}
    Record(const char* key, uint32_t size = 0);
    virtual ~Record();
    
private:
    Record(const Record&);
    Record& operator=(const Record&);

private:
    bool GetStringData(const std::string &srcData, uint32_t start, std::string *retStr);

public:
    bool PaserFromString(const std::string &str);
    bool PaserFromSlice(const util::Slice &str);    
    void SerializeToString(std::string *str) const;
    const std::string& GetKey() const {return mKey;}
    const std::string& GetValue() const {return mValue;}
    RecordType GetType() const {return mRecordType;}        

private:
    std::string mKey;
    std::string mValue;
    RecordType mRecordType;
};

END_SIMPLE_DB_NS(db)

#endif
