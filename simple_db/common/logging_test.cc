#include "logging.h"
#include <gtest/gtest.h>

namespace simple_db {

class LoggingTest : public ::testing::Test {
protected:
    LoggingTest() {

    }
    ~LoggingTest() override {

    }

    void SetUp() override {

    }

    void TearDown() override {

    }

};

TEST_F(LoggingTest, h) {
    Logging::SetLogLevel(Logging::INFO);
    LOG_INFO << "test";
    ASSERT_EQ(0, 0);
}

}


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
