#include "Button.h"

Button::Button(const QString& text, QWidget* parent)
    : QPushButton(text, parent)
{
    setText(text);

    connect(this, SIGNAL(clicked()), this, SLOT(isClicked()));
}

void Button::isClicked()
{
    bool isDigit{};
    const int digit = (this->text()).toInt(&isDigit);

    if (isDigit)
        emit digitClicked(digit);
}
