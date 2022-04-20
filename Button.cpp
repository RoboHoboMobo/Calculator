#include "Button.h"

Button::Button(const QString& text, QWidget* parent)
    : QPushButton(text, parent)
{
    setText(text);
}
