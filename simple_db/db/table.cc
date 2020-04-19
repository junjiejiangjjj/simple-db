#include "table.h"
#include "simple_db/db/mem_table.h"
#include "simple_db/db/record.h"

BEGIN_SIMPLE_DB_NS(db)

Table::Table(const std::string &tableName, const std::string &workDir): mTableName(tableName),
    mTableDir(workDir), mMemTable(new MemTable())
{
}

Table::~Table()
{
    SIMPLE_DB_DELETE_AND_SET_NULL(mMemTable);
}

void Table::Add(const std::string &key, const std::string &value)
{
    std::lock_guard<std::mutex> lock(mMutex);
    mMemTable->Put(key, value, Record::RecordType::VALUE);
}

bool Table::Get(const std::string &key, std::string *value)
{
    std::lock_guard<std::mutex> lock(mMutex);    
    return mMemTable->Get(key, value);
}

void Table::Delete(const std::string &key)
{
    std::lock_guard<std::mutex> lock(mMutex);
    return mMemTable->Put(key, "", Record::RecordType::DELETE);
}


END_SIMPLE_DB_NS(db)

