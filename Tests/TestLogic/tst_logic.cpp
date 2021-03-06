#include <QtTest>

#include "Logic.h"

class TestLogic : public QObject
{
    Q_OBJECT

public:
    TestLogic();
    ~TestLogic();

private slots:
    void writeData();
    void calculateWithoutAnyInput();
    void inputNumber();
    void inputNumberWithDot();
    void plusFirst();
    void minusFirst();
    void multFirst();
    void divFirst();

    void sumTwoNumbers();
    void difTwoNumbers();
    void multTwoNumbers();
    void divTwoNumbers();

    void addAndSub();
    void multAndDiv();
    void addAndMult();

    void logicCalculate();
    void cancelThenPlus();
    void cancelTwice();
};

TestLogic::TestLogic()
{

}

TestLogic::~TestLogic()
{

}

void TestLogic::writeData()
{
    Logic l;

    l.writeDigit(1);
    l.writeDot();
    l.writeDigit(2);
    l.writeDigit(3);
    l.writeDigit(4);

    l.writeOperator(Logic::Operator::Plus);

    l.writeDigit(2);

    l.writeOperator(Logic::Operator::Mult);

    l.writeDigit(3);

    auto actual = l.getOperationsData();

    QVERIFY(actual.size() == 5);
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

    QVERIFY(actual.first);
    QCOMPARE(actual.second, 0.0);

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

void TestLogic::sumTwoNumbers()
{
    Logic l;

    l.writeDigit(1);
    l.writeDigit(2);
    l.writeDot();
    l.writeDigit(3);

    l.writeOperator(Logic::Operator::Plus);

    l.writeDigit(4);
    l.writeDigit(5);
    l.writeDot();
    l.writeDigit(6);

    auto actual = l.calculate();

    QVERIFY(actual.first);
    QCOMPARE(actual.second, 57.9);
}

void TestLogic::difTwoNumbers()
{
    Logic l;

    l.writeDigit(1);
    l.writeDigit(2);
    l.writeDot();
    l.writeDigit(3);

    l.writeOperator(Logic::Operator::Minus);

    l.writeDigit(4);
    l.writeDigit(5);
    l.writeDot();
    l.writeDigit(6);

    auto actual = l.calculate();

    QVERIFY(actual.first);
    QCOMPARE(actual.second, -33.3);
}

void TestLogic::multTwoNumbers()
{
    Logic l;

    l.writeDigit(3);
    l.writeDigit(3);
    l.writeDot();
    l.writeDigit(3);

    l.writeOperator(Logic::Operator::Mult);

    l.writeDigit(3);
    l.writeDot();
    l.writeDigit(0);

    auto actual = l.calculate();

    QVERIFY(actual.first);
    QCOMPARE(actual.second, 99.9);
}

void TestLogic::divTwoNumbers()
{
    Logic l;

    l.writeDigit(4);
    l.writeDot();
    l.writeDigit(8);

    l.writeOperator(Logic::Operator::Div);

    l.writeDigit(2);
    l.writeDot();
    l.writeDigit(4);

    auto actual = l.calculate();

    QVERIFY(actual.first);
    QCOMPARE(actual.second, 2.0);
}

void TestLogic::addAndSub()
{
    Logic l;

    l.writeDigit(1);
    l.writeDot();
    l.writeDigit(2);

    l.writeOperator(Logic::Operator::Plus);

    l.writeDigit(3);
    l.writeDot();
    l.writeDigit(4);

    l.writeOperator(Logic::Operator::Minus);

    l.writeDigit(1);
    l.writeDot();
    l.writeDigit(2);

    auto actual = l.calculate();

    QVERIFY(actual.first);
    QCOMPARE(actual.second, 3.4);
}

void TestLogic::multAndDiv()
{
    Logic l;

    l.writeDigit(1);
    l.writeDot();
    l.writeDigit(2);

    l.writeOperator(Logic::Operator::Mult);

    l.writeDigit(2);

    l.writeOperator(Logic::Operator::Div);

    l.writeDigit(1);
    l.writeDot();
    l.writeDigit(2);

    auto actual = l.calculate();

    QVERIFY(actual.first);
    QCOMPARE(actual.second, 2.0);
}

void TestLogic::addAndMult()
{
    Logic l;

    l.writeDigit(1);
    l.writeDot();
    l.writeDigit(2);

    l.writeOperator(Logic::Operator::Plus);

    l.writeDigit(2);

    l.writeOperator(Logic::Operator::Mult);

    l.writeDigit(2);

    auto actual = l.calculate();

    QVERIFY(actual.first);
    QCOMPARE(actual.second, 5.2);
}

void TestLogic::logicCalculate()
{
    Logic l;

    l.writeDigit(1);
    l.writeOperator(Logic::Operator::Plus);
    l.writeDigit(2);
    l.writeOperator(Logic::Operator::Mult);
    l.writeDigit(3);
    l.writeOperator(Logic::Operator::Minus);
    l.writeDigit(2);
    l.writeOperator(Logic::Operator::Mult);
    l.writeDigit(2);

    auto result = l.calculate();

    QVERIFY(result.first);
}

void TestLogic::cancelThenPlus()
{
    Logic l;

    l.writeDigit(1);
    l.writeDot();
    l.writeDigit(2);
    l.writeDigit(3);

    l.writeOperator(Logic::Operator::Plus);
    l.writeDigit(8);

    l.cancel();
    l.writeDigit(5);

    auto result = l.calculate();

    QVERIFY(result.first);
    QCOMPARE(result.second, 6.23);
}

void TestLogic::cancelTwice()
{
    Logic l;

    l.writeDigit(1);
    l.writeDot();
    l.writeDigit(2);
    l.writeDigit(3);

    l.writeOperator(Logic::Operator::Plus);
    l.writeDigit(8);

    l.cancel();
    l.cancel();

    auto result = l.calculate();

    QVERIFY(result.first);
    QCOMPARE(result.second, 1.23);
}

QTEST_APPLESS_MAIN(TestLogic)

#include "tst_logic.moc"
