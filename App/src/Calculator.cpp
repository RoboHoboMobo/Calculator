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

    m_display = new QLineEdit("0", this);
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
        connect(digits[i], SIGNAL(clicked()), this, SLOT(digitClicked()));

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

void Calculator::digitClicked()
{
    Button* digitButton = qobject_cast<Button*>(sender());

    const int digit = (digitButton->text()).toInt();

    if (m_display->text() == "0") {
        if (digit == 0)
            return;

        m_display->clear();
    }

    m_logic->writeDigit(digit);

    m_display->setText(m_display->text() + QString::number(digit));
}

void Calculator::dotClicked()
{
    m_logic->writeDot();

    m_display->setText(m_display->text() + ".");
}

void Calculator::plusClicked()
{
    m_logic->writeOperator(Logic::Operator::Plus);

    m_display->setText(m_display->text() + " + ");
}

void Calculator::minusClicked()
{
    m_logic->writeOperator(Logic::Operator::Minus);

    m_display->setText(m_display->text() + " - ");
}

void Calculator::multClicked()
{
    m_logic->writeOperator(Logic::Operator::Mult);

    m_display->setText(m_display->text() + " * ");
}

void Calculator::divClicked()
{
    m_logic->writeOperator(Logic::Operator::Div);

    m_display->setText(m_display->text() + " / ");
}

void Calculator::percentClicked()
{
    calculate();
    m_logic->writeOperator(Logic::Operator::Div);
    m_logic->writeDigit(100);

    auto result = calculate();

    if (result.first)
        m_display->setText(QString::number(result.second));
}

void Calculator::equalClicked()
{
    auto result = calculate();

    if (result.first)
        m_display->setText(QString::number(result.second));
}

void Calculator::clearClicked()
{
    m_display->setText("0");

    m_logic->clear();
}

void Calculator::cancelClicked()
{
    auto str = m_display->text();


    if (str.back().isDigit()) {
        if (str.size() && str != "0")
            str.truncate(str.lastIndexOf(' ') + 1);
    }
    else
        str.truncate(lastIndexOfOperator(str) - 1);

    if (str.isEmpty())
        str = "0";

    m_display->setText(str);

    m_logic->cancel();
}

std::pair<bool, double> Calculator::calculate()
{
    auto result = m_logic->getResult();

    if (!result.first) {
        m_display->setText("Error!");

        return {false, 0.0};
    }

    return result;
}
