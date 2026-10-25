#pragma once

#include "LatePenaltyStrategy.h"

class StandardLatePenalty : public LatePenaltyStrategy {
public:
    double calculatePenalty(double hoursLate, double maxMark) const override;
};