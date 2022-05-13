#pragma once

#include <QLineEdit>

#include "Button.h"
#include "IDelegate.h"

#include <memory>

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget* parent = nullptr);

    QString getDisplayText() const;

public slots:
    void receiveResult(const QString&);

private:
    QLineEdit* m_display;
    IDelegate* m_delegate;
};
