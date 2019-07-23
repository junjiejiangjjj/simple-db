#include "logg_stream.h"
#include <gtest/gtest.h>
BEGIN_SIMPLE_DB_NS(util)

class LoggStreamTest : public ::testing::Test {
protected:
    LoggStreamTest() {

    }
    ~LoggStreamTest() override {

    }

    void SetUp() override {

    }

    void TearDown() override {

    }

};

TEST_F(LoggStreamTest, h) {
    ASSERT_EQ(0, 0);
}

END_SIMPLE_DB_NS(util)


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
