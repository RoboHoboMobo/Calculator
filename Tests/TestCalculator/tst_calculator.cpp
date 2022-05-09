#include <QtTest>

#include "Calculator.h"

class TestCalculator : public QObject
{
    Q_OBJECT

public:
    TestCalculator();
    ~TestCalculator();

private slots:
    void checkDefaultText();
    void inputDigit();
    void intputNumber();
};

TestCalculator::TestCalculator()
{
}

TestCalculator::~TestCalculator()
{
}

void TestCalculator::checkDefaultText()
{
    Calculator c;

    QCOMPARE(c.getDisplayText(), "0");
}

void TestCalculator::inputDigit()
{
    Calculator c;

    c.digitClicked(8);

    QCOMPARE(c.getDisplayText(), "8");
}

void TestCalculator::intputNumber()
{
    Calculator c;

    c.digitClicked(1);
    c.digitClicked(2);
    c.dotClicked();
    c.digitClicked(3);

    QCOMPARE(c.getDisplayText(), "12.3");
}

QTEST_MAIN(TestCalculator)

#include "tst_calculator.moc"
