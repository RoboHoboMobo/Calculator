#pragma once

#include <QLineEdit>

#include "Button.h"
#include "Logic.h"

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget* parent = nullptr);

    // std::pair<bool, double> calculate();

public slots:
    void digitClicked();
    void dotClicked();
    void plusClicked();
    void minusClicked();
    void multClicked();
    void divClicked();

    void equalClicked();
    void clearClicked();

private:
    QLineEdit* m_display;
    Logic m_logic;
};
