#ifndef SIMPLE_DB_TABLE_H
#define SIMPLE_DB_TABLE_H

// thread safe table

#include <mutex>
#include <atomic>
#include <thread>
#include <deque>
#include <condition_variable>

#include "simple_db/db/mem_table.h"
#include "simple_db/common/common.h"

BEGIN_SIMPLE_DB_NS(db)


class Writer;

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
    bool Start();
    void Stop();    
    bool Add(const std::string &key, const std::string &value);
    bool Get(const std::string &key, std::string *value);
    bool Delete(const std::string &key);

private:    
    void BatchWrite();
    bool AddToQueue(Writer *);

private:
    std::mutex mMutex;
    std::thread mWriteThread;
    std::condition_variable mNotEmpty;

private:
    std::atomic_bool mStart;
    const std::string mTableName;
    const std::string mTableDir;
    MemTable *mMemTable;
    std::deque<Writer*> mWriteQueue;
    
};

END_SIMPLE_DB_NS(db)

#endif
