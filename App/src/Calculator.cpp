#include "Calculator.h"

#include <Logic.h>

#include <QGridLayout>

#include <array>
#include <cassert>
#include <algorithm>

namespace {

int lastIndexOfOperator(QString str)
{
    return std::max({str.lastIndexOf("+"), str.lastIndexOf("-"),
                     str.lastIndexOf("*"), str.lastIndexOf("/")});
}

} // namespace

Calculator::Calculator(QWidget* parent)
    : QWidget(parent)
    , m_display{}
    , m_logic{}
    , m_isNeedToClear{}
{    
    std::array<Button*, 10> digits;

    for (size_t i = 0; i < 10; ++i)
        digits[i] = new Button(QString::number(i), this);

    Button* clearButton = new Button("C", this);
    Button* cancelButton = new Button("<-", this);

    Button* plusButton = new Button("+", this);
    Button* minusButton = new Button("-", this);
    Button* multButton = new Button("x", this);
    Button* divButton = new Button("/", this);
    Button* percentButton = new Button("%", this);
    Button* dotButton = new Button(".", this);
    Button* equalButton = new Button("=", this);

    m_text = "0";
    m_display = new QLineEdit(m_text, this);
    m_display->setReadOnly(true);
    m_display->setAlignment(Qt::AlignRight);
    m_display->setMaxLength(30);

    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    mainLayout->addWidget(m_display, 0, 0, 1, 4);
    mainLayout->addWidget(clearButton, 1, 0);
    mainLayout->addWidget(cancelButton, 1, 1, 1, 2);
    mainLayout->addWidget(plusButton, 1, 3);
    mainLayout->addWidget(minusButton, 2, 3);
    mainLayout->addWidget(multButton, 3, 3);
    mainLayout->addWidget(divButton, 4, 3);
    mainLayout->addWidget(equalButton, 5, 3);
    mainLayout->addWidget(percentButton, 5, 0);
    mainLayout->addWidget(dotButton, 5, 2);

    assert(digits.size() == 10);

    for (size_t i = 1; i < 10; ++i)
        mainLayout->addWidget(digits[i], 2 + (i - 1)/3, (i - 1) % 3);

    mainLayout->addWidget(digits[0], 5, 1);

    setLayout(mainLayout);

    for (size_t i = 0; i < digits.size(); ++i)
        connect(digits[i], SIGNAL(digitClicked(int)), this, SLOT(digitClicked(int)));

    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
    connect(plusButton, SIGNAL(clicked()), this, SLOT(plusClicked()));
    connect(minusButton, SIGNAL(clicked()), this, SLOT(minusClicked()));
    connect(multButton, SIGNAL(clicked()), this, SLOT(multClicked()));
    connect(divButton, SIGNAL(clicked()), this, SLOT(divClicked()));
    connect(percentButton, SIGNAL(clicked()), this, SLOT(percentClicked()));
    connect(dotButton, SIGNAL(clicked()), this, SLOT(dotClicked()));
    connect(equalButton, SIGNAL(clicked()), this, SLOT(equalClicked()));

    m_logic = std::make_unique<Logic>();
}

QString Calculator::getDisplayText() const
{
    return m_text;
}

void Calculator::digitClicked(int digit)
{
    checkError();

    if (m_isNeedToClear)
        clearAfterEqual();

    if (m_text == "0") {
        if (digit == 0)
            return;

        m_text.clear();
    }

    m_logic->writeDigit(digit);

    m_text += QString::number(digit);
    m_display->setText(m_text);
}

void Calculator::dotClicked()
{
    checkError();

    if (m_isNeedToClear)
        clearAfterEqual();

    m_logic->writeDot();

    m_text += ".";
    m_display->setText(m_text);
}

void Calculator::plusClicked()
{
    checkError();

    m_isNeedToClear = false;

    m_logic->writeOperator(Logic::Operator::Plus);

    m_text += " + ";
    m_display->setText(m_text);
}

void Calculator::minusClicked()
{
    checkError();

    m_isNeedToClear = false;

    m_logic->writeOperator(Logic::Operator::Minus);

    m_text += " - ";
    m_display->setText(m_text);
}

void Calculator::multClicked()
{
    checkError();

    m_isNeedToClear = false;

    m_logic->writeOperator(Logic::Operator::Mult);

    m_text += " * ";
    m_display->setText(m_text);
}

void Calculator::divClicked()
{
    checkError();

    m_isNeedToClear = false;

    m_logic->writeOperator(Logic::Operator::Div);

    m_text += " / ";
    m_display->setText(m_text);
}

void Calculator::percentClicked()
{
    checkError();

    calculate();
    m_logic->writeOperator(Logic::Operator::Div);
    m_logic->writeDigit(100);

    calculate();

    m_isNeedToClear = true;
}

void Calculator::equalClicked()
{
    calculate();

    m_isNeedToClear = true;
}

void Calculator::clearClicked()
{
    m_isNeedToClear = false;

    m_logic->clear();

    m_text = "0";

    m_display->setText(m_text);
}

void Calculator::cancelClicked()
{
    m_isNeedToClear = false;

    m_logic->cancel();

    if (m_text.back().isDigit()) {
        if (m_text.size() && m_text != "0")
            m_text.truncate(m_text.lastIndexOf(' ') + 1);
    }
    else
        m_text.truncate(lastIndexOfOperator(m_text) - 1);

    if (m_text.isEmpty())
        m_text = "0";

    m_display->setText(m_text);
}

std::pair<bool, double> Calculator::calculate()
{
    auto result = m_logic->getResult();

    if (result.first)
        m_text = QString::number(result.second);
    else
        m_text = "Error!";

    m_display->setText(m_text);

    return result;
}

void Calculator::checkError()
{
    if (m_text == "Error!")
    {
        m_logic->clear();

        m_text = "0";
        m_display->setText(m_text);
    }
}

void Calculator::clearAfterEqual()
{
    m_isNeedToClear = false;

    clearClicked();
}
