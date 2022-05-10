#include <QtTest>

#include "Calculator.h"

#include "MockLogic.h"

class TestCalculator : public QObject
{
    Q_OBJECT

public:
    TestCalculator();
    ~TestCalculator();

private slots:
    void checkDefaultText();
    void inputDigit();
    void inputOnlyDot();
    void intputNumberWithDot();
    void checkError();
    void digitAfterError();
    void operatorAfterError();
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

void TestCalculator::inputOnlyDot()
{
    Calculator c;

    c.dotClicked();

    QCOMPARE(c.getDisplayText(), "0.");
}

void TestCalculator::intputNumberWithDot()
{
    Calculator c;

    c.digitClicked(1);
    c.digitClicked(2);
    c.dotClicked();
    c.digitClicked(3);

    QCOMPARE(c.getDisplayText(), "12.3");
}

void TestCalculator::checkError()
{
    Calculator c;

    MockLogic::setResult({false, 0.0});

    c.equalClicked();

    QCOMPARE(c.getDisplayText(), "Error!");
}

void TestCalculator::digitAfterError()
{
    Calculator c;

    MockLogic::setResult({false, 0.0});

    c.equalClicked();
    c.digitClicked(8);

    QCOMPARE(c.getDisplayText(), "8");
}

void TestCalculator::operatorAfterError()
{
    Calculator c;

    MockLogic::setResult({false, 0.0});

    c.equalClicked();
    c.plusClicked();

    QCOMPARE(c.getDisplayText(), "0 + ");
}

QTEST_MAIN(TestCalculator)

#include "tst_calculator.moc"
