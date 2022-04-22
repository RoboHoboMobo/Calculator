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
    m_currentValue = m_currentValue * 10 + digit;
}

void Logic::writeDot()
{
    m_hasDot = true;
}

void Logic::writeOperator(Logic::Operator op)
{
    m_prevValue = m_currentValue;
    m_currentValue = 0.0;

    m_prevOperator = m_currentOperator;
    m_currentOperator = op;
}

double Logic::calculate()
{
    if (m_prevOperator == Operator::None) {
        if (m_currentOperator == Operator::None)
            return m_currentValue;
        else if (m_currentOperator == Operator::Plus)
            return m_sum = m_prevValue + m_currentValue;
        else if (m_currentOperator == Operator::Minus)
            return m_sum = m_prevValue - m_currentValue;
        else if (m_currentOperator == Operator::Mult)
            return m_mult = m_prevValue * m_currentValue;
        else if (m_currentOperator == Operator::Div)
            return m_mult = m_prevValue / m_currentValue;
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

    return m_sum + m_mult;
}
