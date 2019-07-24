#include "slice.h"
#include <gtest/gtest.h>
BEGIN_SIMPLE_DB_NS(util)

class SliceTest : public ::testing::Test {
protected:
    SliceTest() {

    }
    ~SliceTest() override {

    }

    void SetUp() override {

    }

    void TearDown() override {

    }

};

TEST_F(SliceTest, h) {
    std::string s("Test slice");
    Slice sl(s);
    Slice begin("Test");
    ASSERT_TRUE(sl.StartWiths(begin));
    ASSERT_TRUE(sl.Compare(begin) > 0);
    ASSERT_TRUE(sl.Compare(sl) == 0);
    ASSERT_TRUE(sl.Compare(Slice("c")) < 0);
    sl.RemovePrefix(5);
    ASSERT_EQ(sl.Compare(Slice("slice")), 0);
}

END_SIMPLE_DB_NS(util)


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
