#include <QtTest>

#include "Logic.h"

class TestLogic : public QObject
{
    Q_OBJECT

public:
    TestLogic();
    ~TestLogic();

private slots:
    void calculateWithoutAnyInput();
    void inputNumber();
    void inputNumberWithDot();
    void plusFirst();
    void minusFirst();
    void multFirst();
    void divFirst();

};

TestLogic::TestLogic()
{

}

TestLogic::~TestLogic()
{

}

void TestLogic::calculateWithoutAnyInput()
{
    Logic l;
    auto actual = l.calculate();

    QVERIFY(actual.first);
    QCOMPARE(actual.second, 0.0);
}

void TestLogic::inputNumber()
{
    Logic l;
    l.writeDigit(0);
    l.writeDigit(1);
    l.writeDigit(2);
    l.writeDigit(3);

    auto actual = l.calculate();

    QVERIFY(actual.first);
    QCOMPARE(actual.second, 123.0);
}

void TestLogic::inputNumberWithDot()
{
    Logic l;

    l.writeDot();
    l.writeDigit(1);
    l.writeDigit(2);
    l.writeDigit(3);

    auto actual = l.calculate();

    QVERIFY(actual.first);
    QCOMPARE(actual.second, 0.123);

    l.clear();
    l.writeDigit(1);
    l.writeDigit(2);
    l.writeDigit(3);
    l.writeDot();

    actual = l.calculate();

    QVERIFY(actual.first);
    QCOMPARE(actual.second, 123.0);

    l.writeDot();
    l.writeDigit(4);
    l.writeDigit(5);
    l.writeDigit(6);

    actual = l.calculate();

    QVERIFY(actual.first);
    QCOMPARE(actual.second, 123.456);
}

void TestLogic::plusFirst()
{
    Logic l;

    l.writeOperator(Logic::Operator::Plus);

    auto actual = l.calculate();

    QVERIFY(actual.first);
    QCOMPARE(actual.second, 0.0);

    l.clear();
    l.writeOperator(Logic::Operator::Plus);
    l.writeDigit(1);
    l.writeDigit(2);
    l.writeDot();
    l.writeDigit(3);

    actual = l.calculate();

    QVERIFY(actual.first);
    QCOMPARE(actual.second, 12.3);
}

void TestLogic::minusFirst()
{
    Logic l;

    l.writeOperator(Logic::Operator::Minus);

    auto actual = l.calculate();

    QVERIFY(actual.first);
    QCOMPARE(actual.second, 0.0);

    l.clear();
    l.writeOperator(Logic::Operator::Minus);
    l.writeDigit(1);
    l.writeDigit(2);
    l.writeDot();
    l.writeDigit(3);

    actual = l.calculate();

    QVERIFY(actual.first);
    QCOMPARE(actual.second, -12.3);
}

void TestLogic::multFirst()
{
    Logic l;

    l.writeOperator(Logic::Operator::Mult);

    auto actual = l.calculate();

    QVERIFY(actual.first);
    QCOMPARE(actual.second, 0.0);

    l.clear();
    l.writeOperator(Logic::Operator::Mult);
    l.writeDigit(1);
    l.writeDigit(2);
    l.writeDot();
    l.writeDigit(3);

    QVERIFY(actual.first);
    QCOMPARE(actual.second, 0.0);
}

void TestLogic::divFirst()
{
    Logic l;

    l.writeOperator(Logic::Operator::Div);

    auto actual = l.calculate();

    QVERIFY(!actual.first);

    l.clear();
    l.writeOperator(Logic::Operator::Div);
    l.writeDigit(1);
    l.writeDigit(2);
    l.writeDot();
    l.writeDigit(3);

    actual = l.calculate();

    QVERIFY(actual.first);
    QCOMPARE(actual.second, 0.0);
}

QTEST_APPLESS_MAIN(TestLogic)

#include "tst_testlogic.moc"
