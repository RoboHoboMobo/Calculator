#pragma once

#include "OperationsData.h"

#include <utility>

class ILogic
{
public:
    using Operator = enum OperationsData::Operator;

    virtual std::pair<bool, double> getResult() = 0;
    virtual void writeDigit(int) = 0;
    virtual void writeDot() = 0;
    virtual void writeOperator(Operator) = 0;
    virtual void clear() = 0;
    virtual void cancel() = 0;
};
