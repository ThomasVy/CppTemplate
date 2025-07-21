#include <gtest/gtest.h>

class MyTest : public ::testing::Test {
   protected:
    void SetUp() override {
        // Code to set up the test environment
    }

    void TearDown() override {
        // Code to clean up after the test
    }
};

TEST_F(MyTest, ExampleTest) {
    EXPECT_EQ(1, 1);  // This should pass
}
