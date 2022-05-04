#pragma once

#include <QLineEdit>

#include "Button.h"
#include "ILogic.h"

#include <memory>

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
    std::unique_ptr<ILogic> m_logic;
};
