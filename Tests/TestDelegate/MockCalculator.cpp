#include "Calculator.h"

Calculator::Calculator(QWidget* parent)
    : QWidget(parent)
    , m_display{}
    , m_delegate{}
{
}

QString Calculator::getDisplayText() const
{
    return {};
}

void Calculator::receiveResult(const QString&)
{
}
