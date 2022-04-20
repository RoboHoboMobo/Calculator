#pragma once

#include <QLineEdit>

#include "Button.h"

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget* parent = nullptr);

private:
    QLineEdit* m_display;
};
