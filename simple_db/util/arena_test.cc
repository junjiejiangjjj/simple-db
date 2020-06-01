#include "arena.h"
#include <gtest/gtest.h>

BEGIN_SIMPLE_DB_NS(util)

class ArenaTest : public ::testing::Test {
protected:
    ArenaTest() {
    // You can do set-up work for each test here.
    }
    ~ArenaTest() override {
    // You can do clean-up work that doesn't throw exceptions here.
    }
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST_F(ArenaTest, h) {
    Arena a;
    size_t size = 4096;
    char* buf = a.Allocate(size);
    ASSERT_EQ(a.GetToalMem(), size + sizeof(char*));
    a.Allocate(10);
    ASSERT_EQ(a.GetToalMem(), (size + sizeof(char*)) * 2);
    ASSERT_EQ(a.GetReminingBufSize(), size - 10);
    a.Allocate(10);
    ASSERT_EQ(a.GetToalMem(), (size + sizeof(char*)) * 2);
    ASSERT_EQ(a.GetReminingBufSize(), size - 20);
    a.AllocateAligned(17);
    // 3 * 8 - 20 + 17 = 21
    ASSERT_EQ(a.GetReminingBufSize(), size - 41);
}

END_SIMPLE_DB_NS(util)

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
