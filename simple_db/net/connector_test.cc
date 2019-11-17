#include "connector.h"
#include <gtest/gtest.h>
BEGIN_SIMPLE_DB_NS(net)

class ConnectorTest : public ::testing::Test {
protected:
    ConnectorTest() {

    }
    ~ConnectorTest() override {

    }

    void SetUp() override {

    }

    void TearDown() override {

    }

};

TEST_F(ConnectorTest, h) {
    ASSERT_EQ(0, 0);
}

END_SIMPLE_DB_NS(net)


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
