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
    
    {
        std::string value = StringUtil::UInt32ToString(1024, 10);
        ASSERT_EQ(value, "0000001024");

        value = StringUtil::UInt32ToString(1024, 8);
        ASSERT_EQ(value, "00001024");
        
        uint32_t num1 = 0;
        bool valid = StringUtil::StringToUInt32("1234", &num1);
        ASSERT_TRUE(valid);
        ASSERT_EQ(num1, 1234);

        valid = StringUtil::StringToUInt32("51234a", &num1);
        ASSERT_EQ(num1, 51234);        

        ASSERT_TRUE(valid);

        valid = StringUtil::StringToUInt32("aaaaa", &num1);
        ASSERT_FALSE(valid);        
    }

}
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
