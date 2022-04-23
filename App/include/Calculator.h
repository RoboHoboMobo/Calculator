#pragma once

#include <QLineEdit>

#include "Button.h"
#include "Logic.h"

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget* parent = nullptr);

    double calculate();

private:
    QLineEdit* m_display;
    Logic* m_logic;
};
