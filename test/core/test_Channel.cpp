#include <gtest/gtest.h>
#include "core/Channel.h"

class ChannelTest : public ::testing::Test {
protected:
    int imgBuffer[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
    Channel<int> channel{imgBuffer, 4, 3};  // Initialize in declaration
};

TEST_F(ChannelTest, ConstructorTest) {
    EXPECT_EQ(channel.getRows(), 3);
    EXPECT_EQ(channel.getCols(), 4);
}

TEST_F(ChannelTest, GetMinTest) {
    EXPECT_EQ(channel.getMin(), 1);
}

TEST_F(ChannelTest, GetMaxTest) {
    EXPECT_EQ(channel.getMax(), 12);
}

TEST_F(ChannelTest, GetMeanTest) {
    EXPECT_DOUBLE_EQ(channel.getMean(), 6.5);
}