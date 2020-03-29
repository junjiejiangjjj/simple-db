#include "record.h"
#include <gtest/gtest.h>
BEGIN_SIMPLE_DB_NS(db)

class RecordTest : public ::testing::Test {
protected:
    RecordTest() {

    }
    ~RecordTest() override {

    }

    void SetUp() override {

    }

    void TearDown() override {

    }

};

TEST_F(RecordTest, h) {
    {
        Record r1("r1", "teset", Record::RecordType::ADD);
        std::string output;
        r1.SerializeToString(&output);
        Record r2;
        r2.PaserFromString(output);
        ASSERT_EQ(r2.GetKey(), "r1");
        ASSERT_EQ(r2.GetValue(), "teset");
        ASSERT_EQ(r2.GetType(), Record::RecordType::ADD);        
    }

    {
        Record r1("1", "", Record::RecordType::DELETE);
        std::string output;
        r1.SerializeToString(&output);
        Record r2;
        r2.PaserFromString(output);
        ASSERT_EQ(r2.GetKey(), "1");
        ASSERT_EQ(r2.GetValue(), "");
        ASSERT_EQ(r2.GetType(), Record::RecordType::DELETE);
    }    

    {
        Record r1;
        ASSERT_FALSE(r1.PaserFromString(std::string("000100000abc1000000abc")));        
    }

}

END_SIMPLE_DB_NS(db)


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
