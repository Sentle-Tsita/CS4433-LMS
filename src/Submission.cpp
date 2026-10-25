#include "Submission.h"

#include <utility>

using namespace std;

Submission::Submission(int studentId, int assignmentId, string filePath, DateTime submittedAt)
    : studentId_(studentId),
      assignmentId_(assignmentId),
      filePath_(move(filePath)),
      submittedAt_(submittedAt) {}

int Submission::getSubmissionId() const { return submissionId_; }
void Submission::setSubmissionId(int submissionId) { submissionId_ = submissionId; }

int Submission::getStudentId() const { return studentId_; }
int Submission::getAssignmentId() const { return assignmentId_; }
const string& Submission::getFilePath() const { return filePath_; }
DateTime Submission::getSubmittedAt() const { return submittedAt_; }

SubmissionStatus Submission::getStatus() const { return status_; }
void Submission::setStatus(SubmissionStatus status) { status_ = status; }

optional<double> Submission::getMark() const { return mark_; }
void Submission::setMark(double mark) { mark_ = mark; }

const string& Submission::getFeedback() const { return feedback_; }
void Submission::setFeedback(string feedback) { feedback_ = move(feedback); }