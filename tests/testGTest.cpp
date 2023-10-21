#include"gtest/gtest.h"
int func() {
    // assert(false);
    return 0;
}
TEST(ERROR, TERMINATE) {
    // EXPECT_EQ(1, 0);
    EXPECT_EQ(1, 1);
    EXPECT_EQ(func(), 0);
    EXPECT_EQ(1, 1);
    // EXPECT_EXIT()
}
void death() {
    int i = 1/0;
    return;
}
TEST(DEATH, DEATH) {
    EXPECT_DEATH(death(), "");
}
// int main(int argc, char* argv[])
// {
// 	testing::GTEST_FLAG(output) = "xml:";

// 	::testing::InitGoogleTest(&argc, argv);

// 	return RUN_ALL_TESTS();
// }

