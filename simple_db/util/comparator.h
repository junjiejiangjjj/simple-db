#ifndef SIMPLE_DB_COMPARATOR_H
#define SIMPLE_DB_COMPARATOR_H

#include "simple_db/common/common.h" 

BEGIN_SIMPLE_DB_NS(util)

class Slice;

class Comparator {
public:
    Comparator() = default;
    virtual ~Comparator() = default;
private:
    Comparator(const Comparator&) = delete;
    Comparator& operator=(const Comparator&) = delete;

public:
    virtual int Compare(const Slice& a, const Slice& b) const = 0;

    // comparator名，防止创建和读取时使用了不同的comparator
    virtual const char* Name() const = 0;
    // 若start < limit, 返回start和limit之间找一个短字符串，赋值给start
    virtual void FindShortestSeparator(std::string* start, const Slice& limit) const = 0;
    // 将*Key变成一个比源*key大的字符串
    virtual void FindShortestSuccessor(std::string* key) const = 0;
};

const Comparator* BytewiseComparator();

END_SIMPLE_DB_NS(util)

#endif
