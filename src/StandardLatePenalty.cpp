#include "StandardLatePenalty.h"

#include <cmath>

using namespace std;

namespace {

constexpr double kHoursPerDay = 24.0;
constexpr double kMaxLateHours = 72.0;
constexpr double kPenaltyPerDay = 0.10;

}  // namespace

double StandardLatePenalty::calculatePenalty(double hoursLate, double maxMark) const {
    if (hoursLate <= 0.0) {
        return 0.0;
    }
    if (hoursLate > kMaxLateHours) {
        return maxMark;
    }
    double startedDays = ceil(hoursLate / kHoursPerDay);
    return maxMark * kPenaltyPerDay * startedDays;
}