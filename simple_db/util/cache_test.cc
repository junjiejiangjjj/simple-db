#include "cache.h"
#include <gtest/gtest.h>
BEGIN_SIMPLE_DB_NS(util)

class CacheTest : public ::testing::Test {
protected:
    CacheTest() {

    }
    ~CacheTest() override {

    }

    void SetUp() override {

    }

    void TearDown() override {

    }

};

TEST_F(CacheTest, h) {
    ASSERT_EQ(0, 0);
}

END_SIMPLE_DB_NS(util)


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
