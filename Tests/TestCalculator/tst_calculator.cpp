#include <QtTest>

#include "Calculator.h"

class TestCalculator : public QObject
{
    Q_OBJECT

public:
    TestCalculator();
    ~TestCalculator();

private slots:

private:
    Calculator m_calculator;
};

TestCalculator::TestCalculator()
{
}

TestCalculator::~TestCalculator()
{
}

QTEST_MAIN(TestCalculator)

#include "tst_calculator.moc"
