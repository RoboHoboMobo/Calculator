#include "CalculationFrame.h"

CalculationFrame::CalculationFrame()
    : currentValue{0.0}
    , hasCurrentValue{}
    , prevValue{0.0}
    , sum{0.0}
    , mult{0.0}
    , prevOperator{}
    , currentOperator{}
{
}

CalculationFrame::CalculationFrame(double, bool, double, double, double, Operator,
                                   Operator)
    : currentValue{}
    , hasCurrentValue{}
    , prevValue{}
    , sum{}
    , mult{}
    , prevOperator{}
    , currentOperator{}
{
}

std::pair<bool, double> CalculationFrame::calculate()
{
    return {true, 0.0};
}
