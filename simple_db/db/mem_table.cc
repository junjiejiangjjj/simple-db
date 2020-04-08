#include "mem_table.h"


BEGIN_SIMPLE_DB_NS(db)

/**************************** MemTableIter ***********************************************/

class MemTableIter {
public:
    explicit MemTableIter(MemTable::Table *table): mIter(table) {}
    MemTableIter(const MemTableIter &) = delete;
    MemTableIter& operator=(const MemTableIter &) = delete;

    virtual ~MemTableIter() = default;

    bool GetRecord(Record *r);
    void Next();
    bool Valid();
    void Seek(const Record& target);
    
private:
    MemTable::Table::Iterator mIter;
};

bool MemTableIter::GetRecord(Record *record)
{
    if (!record->PaserFromString(mIter.GetKey())) {
        LOG_ERROR << "Not a vaild record: " << mIter.GetKey();
        return false;
    }
    return true;
}

void MemTableIter::Next()
{
    mIter.Next();
}

bool MemTableIter::Valid()
{
    return mIter.Valid();
}

void  MemTableIter::Seek(const Record& target)
{
    std::string recordStr;
    target.SerializeToString(&recordStr);
    mIter.Seek(recordStr.c_str());
}


/******************************************  MemTable ************************************/
    
MemTable::MemTable():mTable(mCmp, &mArena)
{
}

MemTable::~MemTable()
{
}

void MemTable::Put(const std::string &key, const std::string &value, Record::RecordType type)
{
    Record r(key, value, type);
    std::string recordStr;
    r.SerializeToString(&recordStr);
    char* buf = mArena.Allocate(recordStr.size());
    memcpy(buf, recordStr.c_str(), recordStr.size());
    mTable.Insert(buf);
}

bool MemTable::Get(const std::string &key, std::string *value)
{
    Record lookUpKey(key.c_str(), key.size());
    MemTableIter iter(&mTable);
    iter.Seek(lookUpKey);
    Record r;
    if (iter.Valid()) {
        iter.GetRecord(&r);
        if (key == r.GetKey() && r.GetType() == Record::RecordType::VALUE) {
            *value = r.GetValue();
            return true;
        }
        return false;
    }
    return false;
}

END_SIMPLE_DB_NS(db)

