#include <gtest/gtest.h>

#include "Submission.h"

namespace {

Submission makeSubmission() {
    return Submission(7, 3, "uploads/essay.docx", std::chrono::system_clock::now());
}

}  // namespace

TEST(SubmissionTest, NewSubmissionStartsAsSubmittedWithNoMark) {
    Submission submission = makeSubmission();
    EXPECT_EQ(submission.getStatus(), SubmissionStatus::Submitted);
    EXPECT_FALSE(submission.getMark().has_value());
    EXPECT_EQ(submission.getFeedback(), "");
}

TEST(SubmissionTest, ConstructorKeepsTheGivenValues) {
    Submission submission = makeSubmission();
    EXPECT_EQ(submission.getStudentId(), 7);
    EXPECT_EQ(submission.getAssignmentId(), 3);
    EXPECT_EQ(submission.getFilePath(), "uploads/essay.docx");
}

TEST(SubmissionTest, SettingAMarkStoresIt) {
    Submission submission = makeSubmission();
    submission.setMark(15.5);
    ASSERT_TRUE(submission.getMark().has_value());
    EXPECT_DOUBLE_EQ(*submission.getMark(), 15.5);
}

TEST(SubmissionTest, StatusAndFeedbackCanBeChanged) {
    Submission submission = makeSubmission();
    submission.setStatus(SubmissionStatus::Marked);
    submission.setFeedback("Good structure.");
    EXPECT_EQ(submission.getStatus(), SubmissionStatus::Marked);
    EXPECT_EQ(submission.getFeedback(), "Good structure.");
}