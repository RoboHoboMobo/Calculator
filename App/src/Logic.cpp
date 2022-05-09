#include "Logic.h"

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
    auto result = calculate();

    clear();

    if (result.first) {
        m_result = result;
        m_currentValue = m_result.second;
        m_hasCurrentValue = true;

        m_frame.currentValue = m_result.second;
        m_frame.hasCurrentValue = true;
    }

    return result;
}

void Logic::writeDigit(int digit)
{
    m_hasCurrentValue = true;

    if (m_hasDot) {
        m_currentValue += digit * m_dotDivider;
        m_dotDivider /= 10.0;

        return;
    }

    m_currentValue = m_currentValue * 10 + digit;
}

void Logic::writeDot()
{
    if (m_hasDot)
        return;

    m_hasDot = true;
    m_dotDivider = 0.1;
}

void Logic::writeOperator(Logic::Operator op)
{
    m_data.emplace_back(m_currentValue);

    m_currentValue = 0.0;
    m_hasDot = false;
    m_hasCurrentValue = false;

    m_data.emplace_back(op);
}

std::pair<bool, double> Logic::calculate()
{
    if (m_hasCurrentValue && (m_data.back().m_type == OperationsData::Type::Operator ||
                              m_data.empty()))
        m_data.emplace_back(m_currentValue);

    std::pair<bool, double> result{true, 0.0};

    for (auto& data : m_data) {
        if (data.m_type == OperationsData::Type::Operand) {
            m_frame.prevValue = m_frame.currentValue;
            m_frame.currentValue = data.m_operand;

            m_frame.hasCurrentValue = true;

            result = m_frame.calculate();

            if (!result.first)
                return result;
        }
        else if (data.m_type == OperationsData::Type::Operator) {
            m_frame.prevOperator = m_frame.currentOperator;
            m_frame.currentOperator = data.m_operator;

            m_frame.hasCurrentValue = false;
        }
    }

    m_result = result;

    return result;
}

void Logic::clear()
{
    m_data.clear();
    m_frame = {};
    m_currentValue = 0.0;
    m_result = {};
    m_hasDot = {};
    m_dotDivider = 0.0;
    m_hasCurrentValue = {};
}

void Logic::cancel()
{
    if (m_data.size() > 0)
        m_data.pop_back();
}

std::list<OperationsData> Logic::getOperationsData()
{
    if (m_hasCurrentValue)
        m_data.emplace_back(m_currentValue);

    return m_data;
}
