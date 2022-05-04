#include "Logic.h"

Logic::Logic()
    : m_data{}
    , m_frame{}
    , m_currentValue{0.0}
    , m_result{}
    , m_hasDot{}
    , m_dotDivider{0.0}
    , m_hasPreviousValue{}
    , m_hasCurrentValue{}
{
}

std::pair<bool, double> Logic::getResult()
{
    return {true, 0.0};
}

void Logic::writeDigit(int)
{
}

void Logic::writeDot()
{
}

void Logic::writeOperator(Logic::Operator)
{
}

void Logic::clear()
{
}

void Logic::cancel()
{
}

std::pair<bool, double> Logic::calculate()
{
    return {true, 0.0};
}

std::list<OperationsData> Logic::getOperationsData()
{
    return {};
}
