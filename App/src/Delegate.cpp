#include "Delegate.h"

#include "Logic.h"
#include "Calculator.h"

#include <algorithm>

namespace {

int lastIndexOfOperator(QString str)
{
    return std::max({str.lastIndexOf("+"), str.lastIndexOf("-"),
                     str.lastIndexOf("*"), str.lastIndexOf("/")});
}

} // namespace

using Operator = enum OperationsData::Operator;

Delegate::Delegate(Calculator* calculatorPtr)
    : m_calculatorPtr{calculatorPtr}
    , m_result("0")
    , m_isNeedToClear{}
    , m_logic{std::make_unique<Logic>()}
{
    connect(this, SIGNAL(passResultString(const QString&)),
            m_calculatorPtr, SLOT(receiveResult(const QString&)));
}

QString Delegate::getResult() const
{
    return m_result;
}

void Delegate::digitClicked(int digit)
{
    checkError();

    if (m_isNeedToClear)
        clearAfterEqual();

    if (m_result == "0") {
        if (digit == 0)
            return;

        m_result.clear();
    }

    m_logic->writeDigit(digit);
    m_result += QString::number(digit);

    emit (passResultString(m_result));
}

void Delegate::dotClicked()
{
    checkError();

    if (m_isNeedToClear)
        clearAfterEqual();

    m_logic->writeDot();
    m_result += ".";

    emit (passResultString(m_result));
}

void Delegate::plusClicked()
{
    checkError();

    m_isNeedToClear = false;

    m_logic->writeOperator(Operator::Plus);
    m_result += " + ";

    emit (passResultString(m_result));
}

void Delegate::minusClicked()
{
    checkError();

    m_isNeedToClear = false;

    m_logic->writeOperator(Operator::Minus);
    m_result += " - ";

    emit (passResultString(m_result));
}

void Delegate::multClicked()
{
    checkError();

    m_isNeedToClear = false;

    m_logic->writeOperator(Operator::Mult);
    m_result += " * ";

    emit (passResultString(m_result));
}

void Delegate::divClicked()
{
    checkError();

    m_isNeedToClear = false;

    m_logic->writeOperator(Operator::Div);
    m_result += " / ";

    emit (passResultString(m_result));
}

void Delegate::percentClicked()
{
    checkError();

    calculate();
    m_logic->writeOperator(Operator::Div);
    m_logic->writeDigit(100);
    calculate();

    m_isNeedToClear = true;

    emit (passResultString(m_result));
}

void Delegate::equalClicked()
{
    calculate();

    m_isNeedToClear = true;

    emit (passResultString(m_result));
}

void Delegate::clearClicked()
{
    m_isNeedToClear = false;

    m_logic->clear();

    m_result = "0";

    emit (passResultString(m_result));
}

void Delegate::cancelClicked()
{
    m_isNeedToClear = false;

    m_logic->cancel();

    if (m_result.back().isDigit()) {
        if (m_result.size() && m_result != "0")
            m_result.truncate(m_result.lastIndexOf(' ') + 1);
    }
    else
        m_result.truncate(lastIndexOfOperator(m_result) - 1);

    if (m_result.isEmpty())
        m_result = "0";

    emit (passResultString(m_result));
}

std::pair<bool, double> Delegate::calculate()
{
    auto result = m_logic->getResult();

    if (result.first)
        m_result = QString::number(result.second);
    else
        m_result = "Error!";

    return result;
}

void Delegate::checkError()
{
    if (m_result == "Error!")
    {
        m_logic->clear();

        m_result = "0";
        emit (passResultString(m_result));
    }
}

void Delegate::clearAfterEqual()
{
    m_isNeedToClear = false;

    clearClicked();
}
