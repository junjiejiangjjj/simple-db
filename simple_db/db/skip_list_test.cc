#include "skip_list.h"
#include <gtest/gtest.h>
#include "simple_db/db/skip_list.h"

BEGIN_SIMPLE_DB_NS(db)

class SkipListTest : public ::testing::Test {
protected:
    SkipListTest() {

    }
    ~SkipListTest() override {

    }

    void SetUp() override {

    }

    void TearDown() override {

    }

};

typedef uint32_t Key;
struct Comparator {
    int operator() (const Key& a, const Key& b) {
        if (a < b) {
            return -1;
        } else if (a > b) {
            return 1;
        } else {
            return 0;
        }
    }
}

TEST_F(SkipListTest, h) {
    Arena arena;
    Comparator cmp;
    SkipList<Key, Comparator> list(cmp, &arena);
}

END_SIMPLE_DB_NS(db)


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
