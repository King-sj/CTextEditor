
#include"gtest/gtest.h"
#include<svector.h>

#include<sstring.h>
// testing::FLAGS_gtest_color()
// testing::FLAGS_gtest_color
TEST(VectorTest, INT) {
    SVector(int)* ve = newSVector(int)(100);
    EXPECT_EQ(ve->size, 100);
    *SVectorAt(int)(ve, 0) = 999;
    EXPECT_EQ(*SVectorAt(int)(ve, 0),999);
    int* x = SVectorAt(int)(ve, 9999);
    int y = 1e9;
    *x = y;
    EXPECT_EQ(SVectorAt(int)(ve, 9999), x);
    EXPECT_EQ(*SVectorAt(int)(ve, 9999), y);
}

TEST(VectorTest, SString) {
    SVector(SString)* stringVec = newSVector(SString)(100);
    EXPECT_EQ(stringVec->size, 100);
    fillSString(SVectorAt(SString)(stringVec, 0), "hello", 100);
    EXPECT_TRUE(isEqualChars(SVectorAt(SString)(stringVec, 0)->data, "hello"));
}