#include "thread_pool.h"
#include <gtest/gtest.h>
#include<chrono>

BEGIN_SIMPLE_DB_NS(util)

class ThreadPoolTest : public ::testing::Test {
protected:
    ThreadPoolTest() {

    }
    ~ThreadPoolTest() override {

    }

    void SetUp() override {

    }

    void TearDown() override {

    }

};

void func1() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

int get_value(int i, int sleepTime) {
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    return i * i;
}

TEST_F(ThreadPoolTest, h) {
    ThreadPool tp(5);
    tp.Start();
    for (int i = 0; i < 10; ++i) {
        tp.AddTask([i] {func1();});
    }

    for (int i = 0; i < 10; ++i) {
        tp.AddTask([i] {
                get_value(i, i * 100);
            });
    }

    while (!tp.Empty()) {
        std::this_thread::yield();
    }
    
}

END_SIMPLE_DB_NS(util)


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
