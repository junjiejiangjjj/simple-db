#ifndef SIMPLE_DB_SKIP_LIST_H
#define SIMPLE_DB_SKIP_LIST_H


#include "simple_db/common/common.h"
#include "simple_db/util/arena.h"
#include <memory>
#include <ctime>
#include <random>

BEGIN_SIMPLE_DB_NS(db)

template <typename Key, class Comparator>
class SkipList {
private:
    struct Node;
    
public:
    SkipList(Comparator cmp, util::Arena* arena);
    ~SkipList();

private:
    SkipList(const SkipList&) = delete;
    SkipList& operator=(const SkipList&) = delete;

public:
    void Insert(const Key& key);
    bool Contains(const Key& key) const;

private:
    enum { MAX_HEIGHT = 12 };

    inline int GetMaxHeight() const {
        return mMaxHeight;
    }

    
    int RandomHeigth();
    Node* NewNode(const Key &key, int height);
    Node* FindGreaterOrEqual(const Key& key, Node** prev) const;

public:
    class Iterator {
    public:
        explicit Iterator(const SkipList *list): mList(list), mCurNode(list->mHeader->Next(0)) {}
        const Key& GetKey();
        void Next();
        bool Valid() {return mCurNode != nullptr; }

    private:
        const SkipList *mList;
        Node* mCurNode;
    };


private:
    friend class SkipListTest;


private:
    // 当前skip list最大高度
    int mMaxHeight;
    Comparator const mComparator;    
    util::Arena* const mArena;
    Node* const mHeader;

};

// ----------------------------------------- skip list -----------------------------------------------------//

template<typename Key, class Comparator>
SkipList<Key, Comparator>::SkipList(Comparator cmp, util::Arena* arena): mMaxHeight(0),
                                                                         mComparator(cmp),
                                                                         mArena(arena),
                                                                         mHeader(NewNode(0, MAX_HEIGHT))
{
}


template<typename Key, class Comparator>
SkipList<Key, Comparator>::~SkipList()
{
}

template<typename Key, class Comparator>
void SkipList<Key, Comparator>::Insert(const Key &key)
{
    // get node height
    int height = RandomHeigth();
    if (height > mMaxHeight) {
        mMaxHeight = height;
    }

    // create new node
    Node* node = NewNode(key, height);

    // get prevs
    Node* prev[mMaxHeight];
    FindGreaterOrEqual(key, prev);

    // do insert
    for (int i = 0; i < height; i++) {
        if (prev[i] != nullptr) {
            node->AddNext(i, prev[i]->Next(i));
            prev[i]->AddNext(i, node);
        }
    }
}

template<typename Key, class Comparator>
bool SkipList<Key, Comparator>::Contains(const Key& key) const
{
    Node *node = FindGreaterOrEqual(key, nullptr);
    if (node != nullptr && mComparator(key, node->mKey) == 0) {
        return true;
    }
    return false;
}

template<typename Key, class Comparator>
typename SkipList<Key, Comparator>::Node* SkipList<Key, Comparator>::FindGreaterOrEqual(const Key& key, Node** prev) const
{
    Node* node = mHeader;
    int i = mMaxHeight - 1;
    Node* next = node->Next(i);
    while (true) {
        if (next != nullptr && mComparator(next->mKey, key) <= 0 ) {
            node = next;
            next = node->Next(i);
            continue;
        } else {
            if (prev != nullptr)
                prev[i] = node;
            if (i == 0) {
                return node;
            } else {
                --i;
                next = node->Next(i);
            }
        }
    }
}

template<typename Key, class Comparator>
int SkipList<Key, Comparator>::RandomHeigth()
{
    static std::default_random_engine e(time(0));
    static std::uniform_int_distribution<unsigned> u(1, 1024);
    static const unsigned int kBranching = 4;

    // 保证高层数远小于底层数，加快搜索效率
    int height = 1;
    while (height < MAX_HEIGHT && ((u(e) % kBranching) == 0)) {
        height++;
    }
    return height;
}

template<typename Key, class Comparator>
typename SkipList<Key, Comparator>::Node* SkipList<Key, Comparator>::NewNode(const Key &key, int height)
{
    char* const nodeMem =  mArena->AllocateAligned(sizeof(Node) + sizeof(Node*) * (height - 1));
    Node* newNode = new (nodeMem) Node(key);
    for (int i = 0; i < height; i++) {
        newNode->mNext[i] = nullptr;
    }
    return newNode;
}


// --------------------------------------------- iterator ---------------------------------------------------//
template<typename Key, class Comparator>
const Key& SkipList<Key, Comparator>::Iterator::GetKey()
{
    return mCurNode->mKey;
}

template<typename Key, class Comparator>
void SkipList<Key, Comparator>::Iterator::Next()
{
    mCurNode = mCurNode->Next(0);
}


// ---------------------------------------------- node ------------------------------------------------------//
template<typename Key, class Comparator>
struct SkipList<Key, Comparator>::Node {
    explicit Node(Key key);
    Node *Next(int n);
    void AddNext(int n, Node *next);

    const Key mKey;
    Node* mNext[1];

};

template<typename Key, class Comparator>
SkipList<Key, Comparator>::Node::Node(Key key): mKey(key)
{
}

template<typename Key, class Comparator>
void SkipList<Key, Comparator>::Node::AddNext(int n, Node *next)
{
    mNext[n] = next;
}

template<typename Key, class Comparator>
typename SkipList<Key, Comparator>::Node* SkipList<Key, Comparator>::Node::Next(int n)
{
    return mNext[n];
}



END_SIMPLE_DB_NS(db)

#endif
