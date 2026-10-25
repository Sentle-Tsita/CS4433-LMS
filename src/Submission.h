#pragma once

#include <optional>
#include <string>

#include "DateTime.h"
#include "SubmissionStatus.h"

using namespace std;

class Submission {
public:
    Submission(int studentId, int assignmentId, string filePath, DateTime submittedAt);

    int getSubmissionId() const;
    void setSubmissionId(int submissionId);

    int getStudentId() const;
    int getAssignmentId() const;
    const string& getFilePath() const;
    DateTime getSubmittedAt() const;

    SubmissionStatus getStatus() const;
    void setStatus(SubmissionStatus status);

    optional<double> getMark() const;
    void setMark(double mark);

    const string& getFeedback() const;
    void setFeedback(string feedback);

private:
    int submissionId_ = 0;
    int studentId_;
    int assignmentId_;
    string filePath_;
    DateTime submittedAt_;
    SubmissionStatus status_ = SubmissionStatus::Submitted;
    optional<double> mark_;
    string feedback_;
};