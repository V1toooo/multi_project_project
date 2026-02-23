#include <gtest/gtest.h>
#include "long_number.hpp"

using bvs::LongNumber;

TEST(LongNumberTest, Addition) {
    LongNumber a("123");
    LongNumber b("456");
    EXPECT_EQ(a + b, LongNumber("579"));
}

TEST(LongNumberTest, Subtraction) {
    LongNumber a("456");
    LongNumber b("123");
    EXPECT_EQ(a - b, LongNumber("333"));
}

TEST(LongNumberTest, Multiplication) {
    LongNumber a("123");
    LongNumber b("456");
    EXPECT_EQ(a * b, LongNumber("56088"));
}

TEST(LongNumberTest, Division) {
    LongNumber a("100");
    LongNumber b("3");
    EXPECT_EQ(a / b, LongNumber("33"));
}

TEST(LongNumberTest, Modulo) {
    LongNumber a("100");
    LongNumber b("3");
    EXPECT_EQ(a % b, LongNumber("1"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}