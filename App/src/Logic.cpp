#include "Logic.h"

Logic::Logic(QObject* parent)
    : QObject(parent)
    , m_currentValue{0.0}
    , m_prevValue{0.0}
    , m_sum{0.0}
    , m_mult{0.0}
    , m_result{0.0}
    , m_prevOperator{}
    , m_currentOperator{}
    , m_hasDot{}
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
    m_prevValue = m_currentValue;
    m_currentValue = 0.0;
    m_hasDot = false;

    m_prevOperator = m_currentOperator;
    m_currentOperator = op;
}

std::pair<bool, double> Logic::calculate()
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
            if (m_currentValue == 0.0)
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
            m_mult *= m_currentValue;
        }
        else if (m_currentOperator == Operator::Div) {
            m_sum -= m_prevValue;
            m_mult /= m_currentValue;
        }
    }
    else if (m_prevOperator == Operator::Minus) {
        if (m_currentOperator == Operator::Plus)
            m_sum += m_currentValue;
        else if (m_currentOperator == Operator::Minus)
            m_sum -= m_currentValue;
        else if (m_currentOperator == Operator::Mult) {
            m_sum += m_prevValue;
            m_mult *= m_currentValue;
        }
        else if (m_currentOperator == Operator::Div) {
            m_sum += m_prevValue;
            m_mult /= m_currentValue;
        }
    }
    else if (m_prevOperator == Operator::Mult || m_prevOperator == Operator::Div) {
        if (m_currentOperator == Operator::Plus) {
            m_sum += m_mult - m_currentValue;
            m_mult = 0.0;
        }
        else if (m_currentOperator == Operator::Minus) {
            m_sum += m_mult + m_currentValue;
            m_mult = 0.0;
        }
        else if (m_currentOperator == Operator::Mult)
            m_mult *= m_currentValue;
        else if (m_currentOperator == Operator::Div)
            m_mult /= m_currentValue;
    }

    return {true, m_sum + m_mult};
}

void Logic::clear()
{
    m_prevValue = 0.0;
    m_currentValue = 0.0;
    m_sum = 0.0;
    m_mult = 0.0;
    m_result = 0.0;
    m_hasDot = false;
}
