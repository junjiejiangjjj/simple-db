#include "block_queue.h"
#include <gtest/gtest.h>
#include <thread>
#include <future>
#include <vector>

BEGIN_SIMPLE_DB_NS(util)

class BlockQueueTest : public ::testing::Test {
protected:
    BlockQueueTest() {

    }
    ~BlockQueueTest() override {

    }

    void SetUp() override {

    }

    void TearDown() override {

    }

};

void PushTask(BlockQueue<int> &queue)
{
    for (int i = 0; i < 100; ++i) {
        queue.Push(i);
    }
    queue.Push(-1);
}

int TakeTask(BlockQueue<int> &queue)
{
    int count = 0;
    while (true) {
        int tmp = queue.Take();
        if (tmp == -1) {
            return count;
        } else {
            ++count;
        }
    }
}

TEST_F(BlockQueueTest, h) {
    {
        BlockQueue<int> queue;
        std::vector<std::future<void> > pushTasks;
        for (int i = 0; i < 10; ++i) {
            pushTasks.push_back(std::async(PushTask, std::ref(queue)));
        }
    
        std::vector<std::future<int> > takeTasks;
        for (int i = 0; i < 10; ++i) {
            takeTasks.push_back(std::async(TakeTask, std::ref(queue)));
        }
    
        for (auto &f: pushTasks) {
            f.wait();
        }
    
        int count = 0;
        for (auto &f: takeTasks) {
            int ret = f.get();
            count += ret;
        }
    
        ASSERT_EQ(count, pushTasks.size() * 100);
    }

    {
        BlockQueue<std::string> queue;
        std::string tmp = "test";
        queue.Push(std::move(tmp));
        ASSERT_EQ(tmp, "");
        const std::string s = queue.Take();
        ASSERT_EQ(s, "test");
    }

}

END_SIMPLE_DB_NS(util)


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
