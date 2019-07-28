#include "no_destructor.h"
#include <gtest/gtest.h>
BEGIN_SIMPLE_DB_NS(util)

class NoDestructorTest : public ::testing::Test {
protected:
    NoDestructorTest() {

    }
    ~NoDestructorTest() override {

    }

    void SetUp() override {

    }

    void TearDown() override {

    }

};

class DoNotDestructor {
public:
    DoNotDestructor(int a) : mA(a) {}
    ~DoNotDestructor() {
        std::cout<<"destructor"<<std::endl;
        std::abort();
    }

    int mA;
};

TEST_F(NoDestructorTest, h) {
    static NoDestructor<DoNotDestructor> instance(1);
    ASSERT_EQ(instance.get()->mA, 1);
}

END_SIMPLE_DB_NS(util)


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
