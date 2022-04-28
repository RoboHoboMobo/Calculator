#pragma once

#include "OperationsData.h"
#include "CalculationFrame.h"

#include <list>

class Logic
{
public:
    using Operator = enum OperationsData::Operator;

    Logic();

    double getResult() const;
    void writeDigit(int);
    void writeDot();
    void writeOperator(Operator);
    std::pair<bool, double> calculate();
    void clear();

    std::list<OperationsData> getOperationsData();

private:
    std::list<OperationsData> m_data;
    CalculationFrame m_frame;

    double m_currentValue;
    double m_result;
    bool m_hasDot;
    double m_dotDivider;
    bool m_hasPreviousValue;
    bool m_hasCurrentValue;
};
