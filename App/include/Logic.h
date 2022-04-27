#pragma once

#include "OperationsData.h"

#include <QObject>

#include <list>
#include <utility>

class Logic : public QObject
{
    Q_OBJECT

public:
    using Operator = enum OperationsData::Operator;

    struct Frame
    {

    };

    Logic(QObject* parent = nullptr);

    double getResult() const;
    void writeDigit(int);
    void writeDot();
    void writeOperator(Operator);
    std::pair<bool, double> calculate();
    void clear();

    std::list<OperationsData> getOperationsData();

public slots:

private:
    std::list<OperationsData> m_data;

    double m_currentValue;
    double m_prevValue;
    double m_sum;
    double m_mult;
    double m_result;
    Operator m_prevOperator;
    Operator m_currentOperator;
    bool m_hasDot;
    double m_dotDivider;
    bool m_hasPreviousValue;
    bool m_hasCurrentValue;
};
