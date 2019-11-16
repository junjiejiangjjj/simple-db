#include "tcp_server.h"
#include <gtest/gtest.h>
BEGIN_SIMPLE_DB_NS(net)

class TcpServerTest : public ::testing::Test {
protected:
    TcpServerTest() {

    }
    ~TcpServerTest() override {

    }

    void SetUp() override {

    }

    void TearDown() override {

    }

};

TEST_F(TcpServerTest, h) {
    ASSERT_EQ(0, 0);
}

END_SIMPLE_DB_NS(net)


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
