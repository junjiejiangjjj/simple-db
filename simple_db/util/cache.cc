
#include "cache.h"


BEGIN_SIMPLE_DB_NS(util)

namespace {

    struct LRUHandler {
        void* mValue;
        LRUHandler* mNextHash;  // hash table 中使用，解决hash冲突的问题
        LRUHandler* mNext;  // LRUCache中使用，在Cache中相连
        LRUHandler* mPrev;  // 同上
        uint32_t mHash;
        uint32_t mRefs;
        size_t mKeySize;
        char mKey[1];

        Slice Key() const {
            return Slice(mKey, mKeySize);
        }
    };


    class HandleTable {

    public:
        HandleTable() : mSize(0), mCapacity(0), mDataList(nullptr) { Resize(); }
        virtual ~handletable() = default;

        LRUHandler* Insert(LRUHandler* h);
        LRUHandler* Remove(const Slice& key, uint32_t hash);
        LRUHandler* Lookup(const Slice& key, uint32_t hash) {
            return *FindPointer(key, hash);
        }



    private:
        void Resize();
        LRUHandler** FindPointer(const Slice& key, uint32_t hash);

    private:
        LRUHandler **mDataList;
        size_t mCapacity;
        size_t mSize;
    };

    LRUHandler** HandleTable::FindPointer(const Slice& key, uint32_t hash)
    {
        LRUHandler** ptr = &mDataList[hash & (mCapacity - 1)];
        while (*ptr != nullptr && ((*ptr)->mHash != hash || key != (*ptr)->Key())){
            ptr = &(*ptr)->mNextHash;
        }
        return ptr;
    }

    LRUHandler* HandleTable::Insert(LRUHandler* h)
    {
        // 若table中已有相同的handler，新handler替换旧handler，返回旧handler
        LRUHandler** ptr = FindPointer(h->Key(), h->mHash);
        LRUHandler* old = *ptr;
        h->mNextHash = (old == nullptr ? nullptr : old->mNextHash);
        *ptr = h;
        if (old == nullptr) {
            ++mSize;
            if (mSize > mCapacity) {
                Resize();
            }
        }
        return old;
    }

    LRUHandler* HandleTable::Remove(const Slice& key, uint32_t hash)
    {
        LRUHandler** ptr = FindPointer(key, hash);
        LRUHandler* ret = *ptr;
        if (ret != nullptr) {
            *ptr = ret->mNextHash;
            --mSize;
        }
        return ret;
    }

    void HandleTable::Resize()
    {
        uint32_t newCapacity = 4;
        while (newCapacity < mSize) {
            newCapacity *= 2;
        }

        LRUHandler **newList = new LRUHandler*[newCapacity];
        memset(newList, 0, sizeof(newList[0]) * newCapacity);

        // 数据分配到新列表中
        uint32_t count;
        for (uint32_t i = 0; i < mSize; i++) {
            LRUHandler* h = mDataList[i];
            while (h != nullptr) {
                LRUHandler* next = h->mNextHash;
                uint32_t hash = h->mHash;
                LRUHandler** newPos = &newList[hash & (newCapacity - 1)];
                h->mNextHash = *newPos;
                *newPos = h;
                h = next;
                count++;
            }
        }
        assert(mSize == count);
        delete[] mDataList;
        mDataList = newList;
        mCapacity = newCapacity;
    }


    class LRUCache {
    public:
        explicit LRUCache(size_t capacity) { mCapacity = capacity; }
        virtual ~LRUCache() = default;

    private:
        size_t mCapacity;
        Cache::Handler* Insert(const Slice& key, uint32_t hash,
                               void* value, size_t charge);
        Cache::Handler* LookUp(const Slice& key, uint32_t hash);
        void Release(Cache::Handler* handler);
        void Erase(const Slice& key, uint32_t hash);

    };

    // class SharedCache : public {
    // };




} // end anonymous namespace

END_SIMPLE_DB_NS(util)

