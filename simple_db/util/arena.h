#ifndef SIMPLE_DB_ARENA_H
#define SIMPLE_DB_ARENA_H

#include "simple_db/common/common.h"
#include <stddef.h>
#include <assert.h>
#include <vector>
#include <atomic>

BEGIN_SIMPLE_DB_NS(util)


class Arena {
public:
    Arena();
    ~Arena();
private:
    Arena(const Arena &) = delete;
    Arena& operator=(const Arena &) = delete;
public:
    char* Allocate(size_t bytes); 
    char* AllocateAligned(size_t bytes);
private:
    char* AllocateFallback(size_t bytes);
    char* AllocateNewBlock(size_t blockBytes);
public:
    size_t GetToalMem() {return mTotalMem.load(std::memory_order_relaxed);}
    size_t GetReminingBufSize() {return mRemainingBufSize; }
private:
    std::vector<char*> mBlocks;
    size_t mRemainingBufSize;
    std::atomic<size_t> mTotalMem;
    char* mCurAlloc;
};

inline char* Arena::Allocate(size_t bytes){
    if (bytes <= 0) {
        return nullptr;
    }
    if (bytes <= mRemainingBufSize){
        char* cur = mCurAlloc;
        mCurAlloc += bytes;
        mRemainingBufSize -= bytes;
        return cur;
    }
    return AllocateFallback(bytes);
}

END_SIMPLE_DB_NS(util)
#endif
