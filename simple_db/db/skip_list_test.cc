#include "skip_list.h"
#include <gtest/gtest.h>
#include "simple_db/db/skip_list.h"
#include "simple_db/util/slice.h"

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
            std::cout << it.GetKey().GetData() << std::endl;
            ASSERT_EQ(it.GetKey(), except[i]);
            i++;
        }
    }

}

END_SIMPLE_DB_NS(db)


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
