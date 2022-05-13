#include "Calculator.h"

#include "Delegate.h"

#include <QGridLayout>

#include <array>
#include <cassert>

Calculator::Calculator(QWidget* parent)
    : QWidget(parent)
    , m_display{}
    , m_delegate{}
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

    m_delegate = new Delegate(this);

    for (size_t i = 0; i < digits.size(); ++i)
        connect(digits[i], SIGNAL(digitClicked(int)), m_delegate, SLOT(digitClicked(int)));

    connect(clearButton, SIGNAL(clicked()), m_delegate, SLOT(clearClicked()));
    connect(cancelButton, SIGNAL(clicked()), m_delegate, SLOT(cancelClicked()));
    connect(plusButton, SIGNAL(clicked()), m_delegate, SLOT(plusClicked()));
    connect(minusButton, SIGNAL(clicked()), m_delegate, SLOT(minusClicked()));
    connect(multButton, SIGNAL(clicked()), m_delegate, SLOT(multClicked()));
    connect(divButton, SIGNAL(clicked()), m_delegate, SLOT(divClicked()));
    connect(percentButton, SIGNAL(clicked()), m_delegate, SLOT(percentClicked()));
    connect(dotButton, SIGNAL(clicked()), m_delegate, SLOT(dotClicked()));
    connect(equalButton, SIGNAL(clicked()), m_delegate, SLOT(equalClicked()));
}

QString Calculator::getDisplayText() const
{
    return m_display->text();
}

void Calculator::receiveResult(const QString& result)
{
    m_display->setText(result);
}
