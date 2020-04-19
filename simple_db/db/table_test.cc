#include "table.h"
#include <thread>
#include <gtest/gtest.h>

BEGIN_SIMPLE_DB_NS(db)

class TableTest : public ::testing::Test {
protected:
    TableTest() {

    }
    ~TableTest() override {

    }

    void SetUp() override {

    }

    void TearDown() override {

    }

};

TEST_F(TableTest, h) {
    {
        Table table("test_table", "");
        table.Add("test", "xba");
        std::string v;
        bool ret = table.Get("test", &v);
        ASSERT_TRUE(ret);
        ASSERT_EQ(v, "xba");
    }
    {
        Table table("test_table", "");        
        for (int i = 0; i < 100; i++) {
            table.Add(std::to_string(i), std::to_string(i * i));
        }
        for (int i = 0; i < 100; i= i+2) {
            table.Delete(std::to_string(i));
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
    }    
}

void Write(Table *table, int start, int end)
{
    for (int i = start; i < end; i++) {
        (*table).Add(std::to_string(i), std::to_string(i * i));
    }
    std::cout << "Write " << start << " to " << end << " finish" << std::endl;
}

void Delete(Table *table, int start, int end)
{
    for (int i = start; i < end; i++) {
        (*table).Delete(std::to_string(i));
    }
    std::cout << "Delete " << start << " to " << end << " finish" << std::endl;;    
}

TEST(normal, multi_thread) {
    Table  table("test", "");
    std::thread write_t1(Write, &table, 0, 160);
    std::thread write_t2(Write, &table, 100, 200);
    write_t1.join();
    write_t2.join();
    
    std::thread Delete_t1(Delete, &table, 80, 180);
    std::thread Delete_t2(Delete, &table, 10, 150);
    
    Delete_t1.join();
    Delete_t2.join();
    for (int i = 0; i < 200; i++) {
        std::string v;
        bool ret = table.Get(std::to_string(i), &v);
        if (i >= 10 && i < 180) {
            if (ret) {
                std::cout << i << ": " << v << std::endl;
            }
            ASSERT_FALSE(ret);
        } else {
            ASSERT_TRUE(ret);
            ASSERT_EQ(v, std::to_string(i * i));                
        }        
    }
}


END_SIMPLE_DB_NS(db)


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
