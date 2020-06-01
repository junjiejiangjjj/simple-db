#include "simple_db/util/arena.h"

BEGIN_SIMPLE_DB_NS(util)

static const size_t kBlockSize = 4096; //单个block大小

Arena::Arena() {
    mRemainingBufSize = 0;
    mCurAlloc = nullptr;
    mTotalMem = 0;
}
Arena::~Arena() {
    for (auto it: mBlocks){
        delete [] it;
        it = nullptr;
    }
}
char* Arena::AllocateAligned(size_t bytes){
    // 内存对其, sizeof(void*) 64位系统为8 byte
    const int align = (sizeof(void*) > 8) ? sizeof(void*) : 8;
    if ((align & (align-1)) != 0) {
    return nullptr;
    }
    //当前地址可能是未对齐，起点对其到 align整数倍地址，总共分配内存为 取整地址 + bytes
    size_t currentMod = reinterpret_cast<uintptr_t>(mCurAlloc) & (align-1);
    size_t slop = (currentMod == 0 ? 0 : align - currentMod);
    size_t needed = bytes + slop;
    char* result;
    if (needed <= mRemainingBufSize) {
        result = mCurAlloc + slop;
        mCurAlloc += needed;
        mRemainingBufSize -= needed;
    } else {
        result = AllocateFallback(bytes);
    }
    return result;
}
char* Arena::AllocateFallback(size_t bytes){
    if (bytes > kBlockSize / 4){
    // 大于1/4 block直接申请分配
        return AllocateNewBlock(bytes);
    }
    mCurAlloc = AllocateNewBlock(kBlockSize);
    mRemainingBufSize = kBlockSize;
    char* cur = mCurAlloc;
    mCurAlloc += bytes;
    mRemainingBufSize -= bytes;
    return cur;
}
char* Arena::AllocateNewBlock(size_t block_bytes){
    char* ret = new char[block_bytes];
    mBlocks.push_back(ret);
    mTotalMem.fetch_add(block_bytes + sizeof(char*), std::memory_order_relaxed);
    return ret;
}
END_SIMPLE_DB_NS(util)
