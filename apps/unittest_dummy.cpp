#include <gtest/gtest.h>
#include "common.h"

TEST(BitSetTest, BasicOperations) {
    BitSet set1;
    set1.push_back(0xFF);
    set1.push_back(0xAA);
    
    EXPECT_EQ(set1.size(), 2);
    EXPECT_EQ(set1[0], 0xFF);
    EXPECT_EQ(set1[1], 0xAA);
}

TEST(BitSetTest, BitwiseAND) {
    BitSet set1 = {0xFF, 0xF0};
    BitSet set2 = {0x0F, 0xF0};
    
    uint64_t result1 = set1[0] & set2[0];
    uint64_t result2 = set1[1] & set2[1];
    
    EXPECT_EQ(result1, 0x0F);
    EXPECT_EQ(result2, 0xF0);
}
