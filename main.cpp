#include <QApplication>

#include "Calculator.h"

#include <QDebug>
#include "Logic.h"

int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);

    // Calculator c;
    // c.show();

    // return a.exec();

    /// TODO: write autotests
    Logic l;

    l.writeDigit(1);
    qDebug() << l.calculate();
    l.writeDigit(2);
    qDebug() << l.calculate();
    l.writeDigit(3);
    qDebug() << l.calculate();
    l.writeOperator(Logic::Operator::Plus);
    l.writeDigit(5);
    l.writeDigit(0);
    qDebug() << l.calculate();
}
