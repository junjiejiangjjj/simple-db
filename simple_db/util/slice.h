#ifndef SIMPLE_DB_SLICE_H
#define SIMPLE_DB_SLICE_H

#include "simple_db/common/common.h"
#include <string.h>

BEGIN_SIMPLE_DB_NS(util)

class Slice {
public:
    Slice() : mData(""), mSize(0) {}
    Slice(const char* data, size_t size) : mData(data), mSize(size) {}
    Slice(const std::string& s) : mData(s.c_str()), mSize(s.size()) {}
    Slice(const char* s) {
        if (s) {
            mData = s;
            mSize = strlen(s);
        }else {
            mData = "";
            mSize = 0;
        }
    }

    inline const char* GetData() const {return mData;}
    inline size_t GetSize() const {return mSize;}
    inline bool IsEmpty() const {return mSize == 0;}

    char operator[](size_t n) const {
        assert(n < GetSize());
        return mData[n];
    }

    inline void Clear() {
        mData = "";
        mSize = 0;
    }

    inline void RemovePrefix(size_t n) {
        assert(n < GetSize());
        mData += n;
        mSize -= n;
    }

    inline std::string ToString() {return std::string(mData, mSize);}

    int Compare(const Slice&) const;
    inline bool StartWiths(const Slice& x) const {
        return ((mSize >= x.mSize) && (memcmp(mData, x.mData, x.mSize) == 0));
    }


    Slice(const Slice&) = default;
    Slice& operator=(const Slice&) = default;

private:
    const char* mData;
    size_t mSize;
};

inline bool operator==(const Slice& l, const Slice& r) {
    return ((l.GetSize () == r.GetSize()) &&
            (memcmp(l.GetData(), r.GetData(), l.GetSize()) == 0));
}

inline bool operator!=(const Slice& l, const Slice& r) {return !(l == r);}

inline int Slice::Compare(const Slice& r) const {
    const size_t minLen = (mSize < r.mSize) ? mSize : r.mSize;
    int ret = memcmp(mData, r.mData, minLen);
    if (ret == 0) {
        if (mSize < r.mSize) {
            ret =  -1;
        } else if (mSize > r.mSize) {
            ret = 1;
        }
    } else {
        ret = ret > 0 ? 1 : -1;        
    }
    return ret;
}

END_SIMPLE_DB_NS(util)

#endif
