#include "string_util.h"
#include <gtest/gtest.h>
BEGIN_SIMPLE_DB_NS(util)

class StringUtilTest : public ::testing::Test {
protected:
    StringUtilTest() {

    }
    ~StringUtilTest() override {

    }

    void SetUp() override {

    }

    void TearDown() override {

    }

};

TEST_F(StringUtilTest, h) {
    {
        const char* testData = "/Users/local/bin/abc";
        std::string name = StringUtil::GetLatestName(testData);
        ASSERT_EQ(name, "abc");
    }

    {
        const char* testData = "/Users/local/bin/";
        std::string name = StringUtil::GetLatestName(testData);
        ASSERT_EQ(name, "");
    }

    {
        const char* testData = "abc";
        std::string name = StringUtil::GetLatestName(testData);
        ASSERT_EQ(name, "abc");
    }

    {
        std::string s("/Users/lib");
        std::string name = StringUtil::GetLatestName(s);
        ASSERT_EQ(name, "lib");
    }
}

END_SIMPLE_DB_NS(util)


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
