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
        Frame();
        Frame(double currentValue, bool hasCurrentValue, double prevValue, double sum,
              double mult, Operator currentOperator, Operator prevOperator);

        std::pair<bool, double> calculate();

        double m_currentValue;
        bool m_hasCurrentValue;
        double m_prevValue;
        double m_sum;
        double m_mult;
        Operator m_prevOperator;
        Operator m_currentOperator;
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
    Frame m_calcFrame;

    double m_currentValue;
    double m_result;
    bool m_hasDot;
    double m_dotDivider;
    bool m_hasPreviousValue;
    bool m_hasCurrentValue;
};
