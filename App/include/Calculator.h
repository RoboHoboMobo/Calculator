#pragma once

#include <QLineEdit>

#include "Button.h"
#include "Logic.h"

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget* parent = nullptr);

public slots:
    void digitClicked();
    void dotClicked();
    void plusClicked();
    void minusClicked();
    void multClicked();
    void divClicked();
    void percentClicked();

    void equalClicked();
    void clearClicked();
    void cancelClicked();

private:
    std::pair<bool, double> calculate();

    QLineEdit* m_display;
    Logic m_logic;
};
