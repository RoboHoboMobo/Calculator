#pragma once

#include "OperationsData.h"

#include <utility>

struct CalculationFrame
{
    using Operator = enum OperationsData::Operator;

    CalculationFrame();
    CalculationFrame(double currentValue, bool hasCurrentValue, double prevValue,
                     double sum, double mult, Operator currentOperator,
                     Operator prevOperator);

    std::pair<bool, double> calculate();

    double currentValue;
    bool hasCurrentValue;
    double prevValue;
    double sum;
    double mult;
    Operator prevOperator;
    Operator currentOperator;
};
