#include "Logic.h"

Logic::Logic(QObject* parent)
    : QObject(parent)
    , m_currentValue{0.0}
    , m_result{0.0}
    , m_hasDot{}
    , m_dotDivider{0.0}
    , m_hasPreviousValue{}
    , m_hasCurrentValue{}
{
}

double Logic::getResult() const
{
    return m_result;
}

void Logic::writeDigit(int digit)
{
    if (m_hasDot) {
        m_currentValue += digit * m_dotDivider;
        m_dotDivider /= 10.0;

        return;
    }

    m_currentValue = m_currentValue * 10 + digit;

    m_hasCurrentValue = true;
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
    if (m_hasCurrentValue && m_data.back().m_type == OperationsData::Type::Operator)
        m_data.emplace_back(m_currentValue);

    std::pair<bool, double> result;

    for (auto& data : m_data) {
        if (data.m_type == OperationsData::Type::Operand) {
            m_calcFrame.m_prevValue = m_calcFrame.m_currentValue;
            m_calcFrame.m_currentValue = data.m_operand;

            m_calcFrame.m_hasCurrentValue = true;

            result = m_calcFrame.calculate();

            if (!result.first)
                return result;
        }
        else if (data.m_type == OperationsData::Type::Operator) {
            m_calcFrame.m_prevOperator = m_calcFrame.m_currentOperator;
            m_calcFrame.m_currentOperator = data.m_operator;

            m_calcFrame.m_hasCurrentValue = false;
        }
    }

    return result;
}

void Logic::clear()
{
    m_data.clear();
    m_calcFrame = {};
    m_currentValue = 0.0;
    m_result = 0.0;
    m_hasDot = {};
    m_dotDivider = 0.0;
    m_hasPreviousValue = {};
    m_hasCurrentValue = {};
}

std::list<OperationsData> Logic::getOperationsData()
{
    if (m_hasCurrentValue)
        m_data.emplace_back(m_currentValue);

    return m_data;
}

Logic::Frame::Frame()
    : m_currentValue{0.0}
    , m_hasCurrentValue{}
    , m_prevValue{0.0}
    , m_sum{0.0}
    , m_mult{0.0}
    , m_prevOperator{}
    , m_currentOperator{}
{
}

Logic::Frame::Frame(double currentValue, bool hasCurrentValue, double prevValue,
                    double sum, double mult,
                    Operator currentOperator, Operator prevOperator)
    : m_currentValue{currentValue}
    , m_hasCurrentValue{hasCurrentValue}
    , m_prevValue{prevValue}
    , m_sum{sum}
    , m_mult{mult}
    , m_prevOperator{prevOperator}
    , m_currentOperator{currentOperator}
{
}

std::pair<bool, double> Logic::Frame::calculate()
{
    if (m_prevOperator == Operator::None) {
        if (m_currentOperator == Operator::None)
            return {true, m_currentValue};
        else if (m_currentOperator == Operator::Plus)
            return {true, m_sum = m_prevValue + m_currentValue};
        else if (m_currentOperator == Operator::Minus)
            return {true, m_sum = m_prevValue - m_currentValue};
        else if (m_currentOperator == Operator::Mult)
            return {true, m_mult = m_prevValue * m_currentValue};
        else if (m_currentOperator == Operator::Div) {
            if (!m_hasCurrentValue)
                return {true, 0.0};
            else if (m_currentValue == 0.0)
                return {false, 0.0};

            return {true, m_mult = m_prevValue / m_currentValue};
        }
    }

    if (m_prevOperator == Operator::Plus) {
        if (m_currentOperator == Operator::Plus)
            m_sum += m_currentValue;
        else if (m_currentOperator == Operator::Minus)
            m_sum -= m_currentValue;
        else if (m_currentOperator == Operator::Mult) {
            m_sum -= m_prevValue;
            m_mult = m_prevValue * m_currentValue;
        }
        else if (m_currentOperator == Operator::Div) {
            m_sum -= m_prevValue;
            m_mult = m_prevValue / m_currentValue;
        }
    }
    else if (m_prevOperator == Operator::Minus) {
        if (m_currentOperator == Operator::Plus)
            m_sum += m_currentValue;
        else if (m_currentOperator == Operator::Minus)
            m_sum -= m_currentValue;
        else if (m_currentOperator == Operator::Mult) {
            m_sum += m_prevValue;
            m_mult = - m_prevValue * m_currentValue;
        }
        else if (m_currentOperator == Operator::Div) {
            m_sum += m_prevValue;
            m_mult = - m_prevValue / m_currentValue;
        }
    }
    else if (m_prevOperator == Operator::Mult || m_prevOperator == Operator::Div) {
        if (m_currentOperator == Operator::Plus) {
            m_sum += m_mult + m_currentValue;
            m_mult = 0.0;
        }
        else if (m_currentOperator == Operator::Minus) {
            m_sum += m_mult - m_currentValue;
            m_mult = 0.0;
        }
        else if (m_currentOperator == Operator::Mult)
            m_mult *= m_currentValue;
        else if (m_currentOperator == Operator::Div)
            m_mult /= m_currentValue;
    }

    return {true, m_sum + m_mult};
}
