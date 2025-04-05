#include <gtest/gtest.h>
#include "core/Channel.h"

class ChannelTest : public ::testing::Test {
protected:
    int imgBuffer[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
    // Initialize the 1 Channel object with the image buffer and dimensions
    Channel<int> channel{imgBuffer, 4, 3};  // Initialize in declaration

    int imgBuffer2[36] = {1,2,3,4,5,6,7,8,9,10,11,12,
                                    13,14,15,16,17,18,19,20,21,22,
                                    23,24,25,26,27,28,29,30,31,32,
                                    33,34,35,36};
    // Initialize the 3 Channel object with the image buffer and dimensions
    Channel<int> channel2{imgBuffer2, 4, 3, 0};  // Initialize in declaration
    Channel<int> channel3{imgBuffer2, 4, 3, 1};  // Initialize in declaration
    Channel<int> channel4{imgBuffer2, 4, 3, 2};  // Initialize in declaration
};

TEST_F(ChannelTest, ConstructorTest) {
    EXPECT_EQ(channel.getRows(), 3);
    EXPECT_EQ(channel.getCols(), 4);
}

TEST_F(ChannelTest, GetMinTest) {
    EXPECT_EQ(channel.getMin(), 1);
    EXPECT_EQ(channel2.getMin(), 1);
    EXPECT_EQ(channel3.getMin(), 2);
    EXPECT_EQ(channel4.getMin(), 3);
}

TEST_F(ChannelTest, GetMaxTest) {
    EXPECT_EQ(channel.getMax(), 12);
    EXPECT_EQ(channel2.getMax(), 34);
    EXPECT_EQ(channel3.getMax(), 35);
    EXPECT_EQ(channel4.getMax(), 36);
}

TEST_F(ChannelTest, GetMeanTest) {
    EXPECT_DOUBLE_EQ(channel.getMean(), 6.5);
    EXPECT_DOUBLE_EQ(channel2.getMean(), 17.5);
    EXPECT_DOUBLE_EQ(channel3.getMean(), 18.5);
    EXPECT_DOUBLE_EQ(channel4.getMean(), 19.5);
}