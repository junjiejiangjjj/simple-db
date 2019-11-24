#ifndef SIMPLE_DB_SKIP_LIST_H
#define SIMPLE_DB_SKIP_LIST_H


#include "simple_db/common/common.h"
#include "simple_db/util/arena.h"
#include <memory>
#include <random>

BEGIN_SIMPLE_DB_NS(db)

template <typename Key, class Comparator>
class SkipList {
private:
    struct Node;
public:
    SkipList(Comparator cmp, Arena* arena);
    ~SkipList();

private:
    SkipList(const SkipList&) = delete;
    SkipList& operator=(const SkipList&) = delete;

public:
    void Insert(const Key& key);
    bool Contains(const Key& key) const;

private:
    // class Iterator {
    // public:
    //     explicit Iterator(const SkipList* list);
    //     bool Vaild() const;
    //     const Key& key() const;
    //     void Next();
    //     void Prev();
    //     void Seek(const Key& target);
    //     void SeekToFirst();
    //     void SeekToLast();

    // private:
    //     const SkipList* mList;
    //     Node* mNode;
    // };

private:
    enum { MAX_HEIGHT = 12 };

    inline int GetMaxHeight() const {
        return mMaxHeight.load(std::memory_order_relaxed);
    }

    Node* NewNode(const Key& key, int height);
    int RandomHeigth();
    bool Equal(const Key& a, const Key& b) const { return mCompare(a, b); }

    bool KeyIsAfterNode(const Key& key, Node* node) const;
    Node* FindGreaterOrEqual(const Key& key, Node** prev) const;
    // Node* FindLessThan(const Key& key) const;
    // Node* FindLast() const;

private:
    // 当前skip list最大高度
    std::atomic<int> mMaxHeight;
    Node* const mHead;
    Arena* const mArena;
    Comparator const mComparator;

    std::default_random_engine mE;
    std::uniform_int_distri<int> mRandom;

};

template<typename Key, class Comparator>
SkipList::SkipList(Comparator cmp, Arena* arena) : mComparator(cmp), mArena(arena)
                                                 , mHead(NewNode(0, mMaxHeight))
                                                 , mMaxHeight(1), mRandom(1, mE)
{
    for (int i = 0; i < mMaxHeight; i++) {
        mHead->SetNext(i, nullptr);
    }
}

template<typename Key, class Comparator>
int SkipList::<Key, Comparator>::RandomHeigth() {
    return mRandom(mE);
}

template<typename Key, class Comparator>
bool SkipList::KeyIsAfterNode(const Key& key, node* node) const
{
    return (node != nullptr) && (mComparator(node->mKey, key) < 0);
}

template<typename Key, class Comparator>
typename SkipList<Key, Comparator>::Node* NewNode(const Key& key, int height)
{
    
}


template<typename Key, class Comparator>
struct SkipList::Node {
    explicit Node(const Key& key) : mKey(key) {}
    Key const key;

    Node* Next(int n);
    void SetNext(int n, Node* next) {
        std::lock_guard<std::mutex> lock(mMutex);
        mNext[n] = next;
    }

private:
    std::mutex mMutex;
    Node* mNext[1];
};


END_SIMPLE_DB_NS(db)

#endif
