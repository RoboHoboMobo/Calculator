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

    QCOMPARE(l.calculate(), 0.0);
}

void TestLogic::inputNumber()
{
    Logic l;
}

void TestLogic::inputNumberWithDot()
{
    Logic l;
}


QTEST_APPLESS_MAIN(TestLogic)

#include "tst_testlogic.moc"
