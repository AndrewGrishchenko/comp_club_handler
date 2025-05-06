#include <gtest/gtest.h>
#include "ClockTime.h"

class ClockTimeTest : public ::testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(ClockTimeTest, ParseValidTime) {
    ClockTime t;
    EXPECT_TRUE(t.parse("13:45"));
    EXPECT_EQ("13:45", t.str());
}

TEST_F(ClockTimeTest, ParseInvalidFormat) {
    ClockTime t;
    EXPECT_FALSE(t.parse("1:45"));
    EXPECT_FALSE(t.parse("1345"));
    EXPECT_FALSE(t.parse("24:00"));
    EXPECT_FALSE(t.parse("23:60"));
}

TEST_F(ClockTimeTest, StringConversion) {
    ClockTime t(3, 5);
    EXPECT_EQ("03:05", t.str());
}

TEST_F(ClockTimeTest, RoundHourUp) {
    ClockTime t1(10, 0);
    EXPECT_EQ(10, t1.roundHrUp());

    ClockTime t2(10, 1);
    EXPECT_EQ(11, t2.roundHrUp());

    ClockTime t3(10, 59);
    EXPECT_EQ(11, t3.roundHrUp());
}

TEST_F(ClockTimeTest, CompareOperators) {
    ClockTime t1(10, 0);
    ClockTime t2(11, 0);
    EXPECT_TRUE(t1 < t2);
    EXPECT_TRUE(t2 > t1);
    EXPECT_FALSE(t1 > t2);
}

TEST_F(ClockTimeTest, AdditionOperator) {
    ClockTime t1(1, 30);
    ClockTime t2(2, 45);
    ClockTime sum = t1 + t2;
    EXPECT_EQ("04:15", sum.str());
}

TEST_F(ClockTimeTest, SubtractionOperator) {
    ClockTime t1(3, 30);
    ClockTime t2(2, 15);
    ClockTime diff = t1 - t2;
    EXPECT_EQ("01:15", diff.str());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}