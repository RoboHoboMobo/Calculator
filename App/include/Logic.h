#pragma once

#include <QObject>

#include <utility>

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
    std::pair<bool, double> calculate();
    void clear();

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
    double m_dotDivider;
};
