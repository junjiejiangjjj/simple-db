#ifndef SIMPLE_DB_MEM_TABLE_H
#define SIMPLE_DB_MEM_TABLE_H

#include "simple_db/common/common.h"
#include "simple_db/db/skip_list.h"
#include "simple_db/util/arena.h"
#include "simple_db/util/slice.h"
#include "simple_db/db/record.h"

BEGIN_SIMPLE_DB_NS(db)


class MemTable {
public:
    MemTable();
    virtual ~MemTable();
private:
    MemTable(const MemTable&);
    MemTable& operator=(const MemTable&);

public:
    void Put(const std::string &key, const std::string &value, Record::RecordType type);
    bool Get(const std::string &key, std::string *value);
    size_t ApproximateMemoryUsage() { return mArena.GetToalMem(); }

private:
    struct TableComparator {
        int operator() (const char* a, const char* b) const {
            Record ar, br;
            ar.PaserFromString(a);
            br.PaserFromString(b);
            int ret = ar.GetKey().compare(br.GetKey());
            if (ret < 0) {
                return -1;
            } else if (ret == 0) {
                return 0;
            } else {
                return 1;
            }
        }
    };


public:
    typedef SkipList<const char*, TableComparator> Table;
    
private:
    util::Arena mArena;
    TableComparator mCmp;
    Table mTable;
};

END_SIMPLE_DB_NS(db)

#endif
