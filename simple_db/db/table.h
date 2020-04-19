#ifndef SIMPLE_DB_TABLE_H
#define SIMPLE_DB_TABLE_H

// thread safe table

#include <mutex>

#include "simple_db/db/mem_table.h"
#include "simple_db/common/common.h"

BEGIN_SIMPLE_DB_NS(db)


class Table {

public:
    Table(const std::string &tableName, const std::string &workDir);
    virtual ~Table();
private:
    Table(const Table&);
    Table& operator=(const Table&);

public:
    const std::string &TableName() { return mTableName; }

public:
    void Add(const std::string &key, const std::string &value);
    bool Get(const std::string &key, std::string *value);
    void Delete(const std::string &key);

private:
    std::mutex mMutex;
    

private:
    const std::string mTableName;
    const std::string mTableDir;
    MemTable *mMemTable;
    
};

END_SIMPLE_DB_NS(db)

#endif
