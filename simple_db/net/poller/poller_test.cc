#include "poller.h"
#include <gtest/gtest.h>
BEGIN_SIMPLE_DB_NS(poller)

class PollerTest : public ::testing::Test {
protected:
    PollerTest() {

    }
    ~PollerTest() override {

    }

    void SetUp() override {

    }

    void TearDown() override {

    }

};

TEST_F(PollerTest, h) {
    ASSERT_EQ(0, 0);
}

END_SIMPLE_DB_NS(poller)


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
