#pragma once

#include <QObject>

class Logic : public QObject
{
    Q_OBJECT

public:
    enum Operator {
        None = 0,
        Plus,
        Minus,
        Mult,
        Div
    };

    Logic(QObject* parent = nullptr);

    double getResult() const;
    void writeDigit(int);
    void writeDot();
    void writeOperator(Operator);
    double calculate();

public slots:

private:
    double m_currentValue;
    double m_prevValue;
    double m_sum;
    double m_mult;
    double m_result;
    Operator m_prevOperator;
    Operator m_currentOperator;
    bool m_hasDot;
};
