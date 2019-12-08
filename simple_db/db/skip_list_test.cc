#include "skip_list.h"
#include <gtest/gtest.h>
#include "simple_db/db/skip_list.h"

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
};



TEST_F(SkipListTest, h) {

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

END_SIMPLE_DB_NS(db)


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
