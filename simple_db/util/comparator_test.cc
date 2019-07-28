#include "slice.h"
#include "comparator.h"
#include <gtest/gtest.h>
BEGIN_SIMPLE_DB_NS(util)

class ComparatorTest : public ::testing::Test {
protected:
    ComparatorTest() {

    }
    ~ComparatorTest() override {

    }

    void SetUp() override {

    }

    void TearDown() override {

    }

};

TEST_F(ComparatorTest, h) {
    const Comparator *cmp = BytewiseComparator();
    ASSERT_TRUE(cmp->Compare(Slice("test"), Slice("test")) == 0);
    ASSERT_TRUE(cmp->Compare(Slice("test"), Slice("test3")) < 0);
    ASSERT_TRUE(cmp->Compare(Slice("test"), Slice("tes")) > 0);
}

END_SIMPLE_DB_NS(util)


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
