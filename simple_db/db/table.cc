#include "table.h"
#include "simple_db/db/mem_table.h"
#include "simple_db/db/record.h"
#include <mutex>
#include <condition_variable>

BEGIN_SIMPLE_DB_NS(db)


class Writer {
public:
    Writer() {}
    
    bool done = false;
    std::condition_variable mCv;
    std::string k;
    std::string v;
    Record::RecordType rType;
};


Table::Table(const std::string &tableName, const std::string &workDir):
    mStart(false),
    mTableName(tableName),
    mTableDir(workDir),
    mMemTable(new MemTable())
{
}

Table::~Table()
{
    Stop();
    SIMPLE_DB_DELETE_AND_SET_NULL(mMemTable);
}

bool Table::Add(const std::string &key, const std::string &value)
{
    if (!mStart) {
        return false;
    }
    
    Writer w;
    w.k = key;
    w.v = value;
    w.rType = Record::RecordType::VALUE;
    
    return AddToQueue(&w);
}

bool Table::AddToQueue(Writer *w)
{
    if (!mStart) {
        LOG_ERROR << "Table already stop, can not write";
        return false;
    }
    
    std::unique_lock<std::mutex> lock(mMutex);
    mWriteQueue.push_back(w);
    mNotEmpty.notify_one();
    while (!w->done) {
        w->mCv.wait(lock, [&] {return w->done;});
    }
    return true;
}

bool Table::Start()
{
    mWriteThread = std::thread(&Table::BatchWrite, this);
    mStart = true;
    return true;
}

void Table::Stop()
{
    if (mStart) {
        // do stop
        mStart = false;
        {
            std::unique_lock<std::mutex> lock(mMutex);
            // notify batch write stop
            LOG_INFO << "Push nullptr";
            mWriteQueue.push_back(nullptr);
            mNotEmpty.notify_one();
        }
        
        mWriteThread.join();
        LOG_INFO << "Success stop table";
        assert(mWriteQueue.size() == 0);
    }
}

void Table::BatchWrite()
{
    while (true) {
        Writer* w = nullptr;
        {
            std::unique_lock<std::mutex> lock(mMutex);     
            while (mWriteQueue.empty()) {
                mNotEmpty.wait(lock, [this]{ return !mWriteQueue.empty();});
            }
        
            w = mWriteQueue.front();
            mWriteQueue.pop_front();
        }
        
        if (w == nullptr) {
            break;
        }
        mMemTable->Put(w->k, w->v, w->rType);
        w->done = true;
        w->mCv.notify_one();
    }
}

bool Table::Get(const std::string &key, std::string *value)
{
    return mMemTable->Get(key, value);
}

bool Table::Delete(const std::string &key)
{
    if (!mStart) {
        return false;
    }
    
    Writer w;
    w.k = key;
    w.rType = Record::RecordType::DELETE;
    return AddToQueue(&w);    
}


END_SIMPLE_DB_NS(db)

