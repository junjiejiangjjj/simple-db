#include "skip_list.h"
#include <gtest/gtest.h>
#include "simple_db/db/skip_list.h"
#include "simple_db/util/slice.h"
#include <thread>

BEGIN_SIMPLE_DB_NS(db)

struct Comparator {
    int operator() (const int& a, const int& b) const {
        if (a < b) {
            return -1;
        } else if (a > b) {
            return 1;
        } else {
            return 0;
        }
    }
};


struct SliceComparator {
    int operator() (const util::Slice& a, const util::Slice& b) const {
        return a.Compare(b);
    }
};


class SkipListTest : public ::testing::Test {
protected:
    SkipListTest(){
    }
    ~SkipListTest() override {

    }

    void SetUp() override {

    }

    void TearDown() override {

    }

    util::Arena mArena;
    Comparator mCmp;
    SliceComparator mSliceCmp;
};



TEST_F(SkipListTest, h) {
    {
        SkipList<int, Comparator> list(mCmp, &mArena);

        list.Insert(1);
        list.Insert(2);
        list.Insert(7);
        list.Insert(3);
        ASSERT_TRUE(list.Contains(1));
        ASSERT_TRUE(list.Contains(7));
        ASSERT_FALSE(list.Contains(10));

        SkipList<int, Comparator>::Iterator it(&list);
        int i = 0;
        int except[4] = {1,2,3,7};
        for (; it.Valid(); it.Next()) {
            ASSERT_EQ(it.GetKey(), except[i]);
            i++;
        }        
    }
    
    {
        SkipList<util::Slice, SliceComparator> list(mSliceCmp, &mArena);
        list.Insert("abc");
        list.Insert("adc");
        list.Insert("bcd");
        list.Insert("abc");
        ASSERT_TRUE(list.Contains("abc"));
        ASSERT_TRUE(list.Contains("bcd"));
        ASSERT_FALSE(list.Contains("ccc"));

        SkipList<util::Slice, SliceComparator>::Iterator it(&list);
        int i = 0;
        std::string except[4] = {"abc", "abc", "adc", "bcd"};
        for (; it.Valid(); it.Next()) {
            ASSERT_EQ(it.GetKey(), except[i]);
            i++;
        }

        it.Seek("ad");
        i = 2;
        for (; it.Valid(); it.Next()) {
            ASSERT_EQ(it.GetKey(), except[i]);
            i++;
        }
    }
}

void WriteThread(SkipList<int, Comparator> &list){
    for (int i = 0; i < 1000; ++i) {
        list.Insert(i);
    }
}

void ReadThread(SkipList<int, Comparator> &list, int i, bool check){
    while (true) {
        bool ret = list.Contains(i);
        if (check) {
            if (i < 1000) {
                ASSERT_TRUE(ret);
            } else {
                ASSERT_FALSE(ret);            
            }            
        }

        ++i;
        if (i > 2000) {
            break;
        }
    }
    
}

TEST_F(SkipListTest, multi_thread) {
    // 一写多读
    SkipList<int, Comparator> list(mCmp, &mArena);
    std::thread ws = std::thread([&list] { WriteThread(list); });
    std::vector<std::thread> ts;
    for (int i = 0; i < 100; ++i) {
        ts.push_back(std::thread([&list, i] { ReadThread(list, i, false); }));
    }
    for (auto &t: ts) {
        t.join();
    }

    ws.join();
    ts.clear();
    for (int i = 0; i < 100; ++i) {
        ts.push_back(std::thread([&list, i] { ReadThread(list, i, true); }));
    }
    for (auto &t: ts) {
        t.join();
    }    
}

END_SIMPLE_DB_NS(db)


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
