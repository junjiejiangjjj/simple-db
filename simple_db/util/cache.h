#ifndef SIMPLE_DB_CACHE_H
#define SIMPLE_DB_CACHE_H

#include "simple_db/common/common.h"
#include "simple_db/util/slice.h"

BEGIN_SIMPLE_DB_NS(util)

class Cache {

public:
    Cache() = default;
    virtual ~Cache() = default;

private:
    Cache(const Cache&) = delete;
    Cache& operator=(const Cache&) = delete;

public:
    // 不暴露具体类，只暴露一个对象句柄，对Handler所有的操作都是通过接口来实现
    // C++中空类占一个字节，可以用于定位一个对象
    struct Handler {};


    virtual Handler* Insert(const Slice& key, void* value, size_t charge) = 0;
    virtual Handler* Lookup(const Slice& key) = 0;
    virtual void Release(Handler*) = 0;
    virtual void* Value(Handler*) = 0;
    virtual void Erase(const Slice&) = 0;

};

END_SIMPLE_DB_NS(util)

#endif
