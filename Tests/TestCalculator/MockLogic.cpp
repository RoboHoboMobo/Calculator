#include "MockLogic.h"

namespace {

std::pair<bool, double> mockResult{};

} // namespace

void MockLogic::setResult(std::pair<bool, double> result)
{
    mockResult = result;
}

Logic::Logic()
    : m_data{}
    , m_frame{}
    , m_currentValue{0.0}
    , m_result{}
    , m_hasDot{}
    , m_dotDivider{0.0}
    , m_hasCurrentValue{}
{
}

std::pair<bool, double> Logic::getResult()
{
    return mockResult;
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
