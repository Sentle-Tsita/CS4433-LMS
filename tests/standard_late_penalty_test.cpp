#include <gtest/gtest.h>

#include "StandardLatePenalty.h"

namespace {

constexpr double kMaxMark = 20.0;
constexpr double kOneSecondInHours = 1.0 / 3600.0;

}  // namespace

TEST(StandardLatePenaltyTest, OnTimeSubmissionHasNoPenalty) {
    StandardLatePenalty penalty;
    EXPECT_DOUBLE_EQ(penalty.calculatePenalty(0.0, kMaxMark), 0.0);
}

TEST(StandardLatePenaltyTest, EarlySubmissionHasNoPenalty) {
    StandardLatePenalty penalty;
    EXPECT_DOUBLE_EQ(penalty.calculatePenalty(-5.0, kMaxMark), 0.0);
}

TEST(StandardLatePenaltyTest, OneSecondLateIsFirstDay) {
    StandardLatePenalty penalty;
    EXPECT_DOUBLE_EQ(penalty.calculatePenalty(kOneSecondInHours, kMaxMark), 2.0);
}

TEST(StandardLatePenaltyTest, ExactlyTwentyFourHoursIsStillFirstDay) {
    StandardLatePenalty penalty;
    EXPECT_DOUBLE_EQ(penalty.calculatePenalty(24.0, kMaxMark), 2.0);
}

TEST(StandardLatePenaltyTest, OneSecondOverTwentyFourHoursIsSecondDay) {
    StandardLatePenalty penalty;
    EXPECT_DOUBLE_EQ(penalty.calculatePenalty(24.0 + kOneSecondInHours, kMaxMark), 4.0);
}

TEST(StandardLatePenaltyTest, TwentyFiveHoursLateIsSecondDay) {
    StandardLatePenalty penalty;
    EXPECT_DOUBLE_EQ(penalty.calculatePenalty(25.0, kMaxMark), 4.0);
}

TEST(StandardLatePenaltyTest, ExactlyFortyEightHoursIsStillSecondDay) {
    StandardLatePenalty penalty;
    EXPECT_DOUBLE_EQ(penalty.calculatePenalty(48.0, kMaxMark), 4.0);
}

TEST(StandardLatePenaltyTest, ExactlySeventyTwoHoursIsThirdDay) {
    StandardLatePenalty penalty;
    EXPECT_DOUBLE_EQ(penalty.calculatePenalty(72.0, kMaxMark), 6.0);
}

TEST(StandardLatePenaltyTest, OneSecondOverSeventyTwoHoursLosesWholeMark) {
    StandardLatePenalty penalty;
    EXPECT_DOUBLE_EQ(penalty.calculatePenalty(72.0 + kOneSecondInHours, kMaxMark), kMaxMark);
}

TEST(StandardLatePenaltyTest, HundredHoursLateLosesWholeMark) {
    StandardLatePenalty penalty;
    EXPECT_DOUBLE_EQ(penalty.calculatePenalty(100.0, kMaxMark), kMaxMark);
}