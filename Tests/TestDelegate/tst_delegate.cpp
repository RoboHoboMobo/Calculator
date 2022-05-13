#include <QtTest>

#include "Delegate.h"
#include "Calculator.h"

#include "MockLogic.h"

class TestDelegate : public QObject
{
    Q_OBJECT

public:
    TestDelegate();
    ~TestDelegate();

private slots:
    void checkDefaultText();
    void inputDigit();
    void inputOnlyDot();
    void intputNumberWithDot();
    void checkError();
    void digitAfterError();
    void operatorAfterError();
    void inputNumberAfterEqual();
    void inputNumberAfterPercent();

private:
    Calculator m_calculator;
};

TestDelegate::TestDelegate()
{
}

TestDelegate::~TestDelegate()
{
}

void TestDelegate::checkDefaultText()
{
    Delegate d(&m_calculator);

    QCOMPARE(d.getResult(), "0");
}

void TestDelegate::inputDigit()
{
    Delegate d(&m_calculator);

    d.digitClicked(8);

    QCOMPARE(d.getResult(), "8");
}

void TestDelegate::inputOnlyDot()
{
    Delegate d(&m_calculator);

    d.dotClicked();

    QCOMPARE(d.getResult(), "0.");
}

void TestDelegate::intputNumberWithDot()
{
    Delegate d(&m_calculator);

    d.digitClicked(1);
    d.digitClicked(2);
    d.dotClicked();
    d.digitClicked(3);

    QCOMPARE(d.getResult(), "12.3");
}

void TestDelegate::checkError()
{
    Delegate d(&m_calculator);

    MockLogic::setResult({false, 0.0});

    d.equalClicked();

    QCOMPARE(d.getResult(), "Error!");
}

void TestDelegate::digitAfterError()
{
    Delegate d(&m_calculator);

    MockLogic::setResult({false, 0.0});

    d.equalClicked();
    d.digitClicked(8);

    QCOMPARE(d.getResult(), "8");
}

void TestDelegate::operatorAfterError()
{
    Delegate d(&m_calculator);

    MockLogic::setResult({false, 0.0});

    d.equalClicked();
    d.plusClicked();

    QCOMPARE(d.getResult(), "0 + ");
}

void TestDelegate::inputNumberAfterEqual()
{
    Delegate d(&m_calculator);

    d.digitClicked(1);
    d.dotClicked();
    d.digitClicked(2);
    d.digitClicked(3);

    d.equalClicked();

    d.digitClicked(8);

    QCOMPARE(d.getResult(), "8");
}

void TestDelegate::inputNumberAfterPercent()
{
    Delegate d(&m_calculator);

    d.digitClicked(1);
    d.digitClicked(2);
    d.digitClicked(3);

    d.percentClicked();

    d.digitClicked(8);

    QCOMPARE(d.getResult(), "8");
}

QTEST_MAIN(TestDelegate)

#include "tst_delegate.moc"
