#include "mem_table.h"
#include <gtest/gtest.h>
BEGIN_SIMPLE_DB_NS(db)

class MemTableTest : public ::testing::Test {
protected:
    MemTableTest() {

    }
    ~MemTableTest() override {

    }

    void SetUp() override {

    }

    void TearDown() override {

    }

};

TEST_F(MemTableTest, h) {
    {
        MemTable table;
        table.Put("test", "xba", Record::RecordType::VALUE);
        std::string v;
        bool ret = table.Get("test", &v);
        ASSERT_TRUE(ret);
        ASSERT_EQ(v, "xba");
        std::cout << table.ApproximateMemoryUsage() << std::endl;
    }
    {
        MemTable table;        
        for (int i = 0; i < 100; i++) {
            table.Put(std::to_string(i), std::to_string(i * i), Record::RecordType::VALUE);
        }
        for (int i = 0; i < 100; i= i+2) {
            table.Put(std::to_string(i), std::to_string(i * i), Record::RecordType::DELETE);
        }
        for (int i = 0; i < 100; i++) {
            std::string v;
            bool ret = table.Get(std::to_string(i), &v);
            if (i % 2 == 0) {
                ASSERT_FALSE(ret);
            } else {
                ASSERT_TRUE(ret);
                ASSERT_EQ(v, std::to_string(i * i));                
            }
        }
        std::cout << table.ApproximateMemoryUsage() << std::endl;        
    }
}

END_SIMPLE_DB_NS(db)


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
