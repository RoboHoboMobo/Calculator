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

    QString getDisplayText() const;

public slots:
    void digitClicked(int);
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
    void checkError();
    void clearAfterEqual();

    QLineEdit* m_display;
    QString m_text;
    std::unique_ptr<ILogic> m_logic;
    bool m_isNeedToClear;
};
