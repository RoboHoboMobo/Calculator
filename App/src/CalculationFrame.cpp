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

CalculationFrame::CalculationFrame(double currentValue, bool hasCurrentValue,
                                          double prevValue, double sum, double mult,
                                          Operator currentOperator, Operator prevOperator)
    : currentValue{currentValue}
    , hasCurrentValue{hasCurrentValue}
    , prevValue{prevValue}
    , sum{sum}
    , mult{mult}
    , prevOperator{prevOperator}
    , currentOperator{currentOperator}
{
}

std::pair<bool, double> CalculationFrame::calculate()
{
    if (prevOperator == Operator::None) {
        if (currentOperator == Operator::None)
            return {true, currentValue};
        else if (currentOperator == Operator::Plus)
            return {true, sum = prevValue + currentValue};
        else if (currentOperator == Operator::Minus)
            return {true, sum = prevValue - currentValue};
        else if (currentOperator == Operator::Mult)
            return {true, mult = prevValue * currentValue};
        else if (currentOperator == Operator::Div) {
            if (!hasCurrentValue)
                return {true, 0.0};
            else if (currentValue == 0.0)
                return {false, 0.0};

            return {true, mult = prevValue / currentValue};
        }
    }

    if (prevOperator == Operator::Plus) {
        if (currentOperator == Operator::Plus)
            sum += currentValue;
        else if (currentOperator == Operator::Minus)
            sum -= currentValue;
        else if (currentOperator == Operator::Mult) {
            sum -= prevValue;
            mult = prevValue * currentValue;
        }
        else if (currentOperator == Operator::Div) {
            sum -= prevValue;
            mult = prevValue / currentValue;
        }
    }
    else if (prevOperator == Operator::Minus) {
        if (currentOperator == Operator::Plus)
            sum += currentValue;
        else if (currentOperator == Operator::Minus)
            sum -= currentValue;
        else if (currentOperator == Operator::Mult) {
            sum += prevValue;
            mult = - prevValue * currentValue;
        }
        else if (currentOperator == Operator::Div) {
            sum += prevValue;
            mult = - prevValue / currentValue;
        }
    }
    else if (prevOperator == Operator::Mult || prevOperator == Operator::Div) {
        if (currentOperator == Operator::Plus) {
            sum += mult + currentValue;
            mult = 0.0;
        }
        else if (currentOperator == Operator::Minus) {
            sum += mult - currentValue;
            mult = 0.0;
        }
        else if (currentOperator == Operator::Mult)
            mult *= currentValue;
        else if (currentOperator == Operator::Div)
            mult /= currentValue;
    }

    return {true, sum + mult};
}
