#pragma once

#include "ILogic.h"
#include "OperationsData.h"
#include "CalculationFrame.h"

#include <list>

class Logic : public ILogic
{
public:
    Logic();

    std::pair<bool, double> getResult() override;
    void writeDigit(int) override;
    void writeDot() override;
    void writeOperator(Operator) override;
    void clear() override;
    void cancel() override;

    std::pair<bool, double> calculate();
    std::list<OperationsData> getOperationsData();

private:
    std::list<OperationsData> m_data;
    CalculationFrame m_frame;

    double m_currentValue;
    std::pair<bool, double> m_result;
    bool m_hasDot;
    double m_dotDivider;
    bool m_hasPreviousValue;
    bool m_hasCurrentValue;
};
