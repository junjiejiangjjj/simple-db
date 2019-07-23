#include "logging.h"
#include <gtest/gtest.h>
BEGIN_SIMPLE_DB_NS(util)

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

END_SIMPLE_DB_NS(util)


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
