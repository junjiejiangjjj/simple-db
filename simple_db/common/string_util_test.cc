#include "string_util.h"
#include <gtest/gtest.h>

namespace simple_db {
    

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

    {
        std::string t = StringUtil::GetTimeString("%Y-%m-%d %H:%M:%S");
        std::cout<< t <<std::endl;
    }
}
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
