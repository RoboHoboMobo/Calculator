#include <QApplication>

#include "Calculator.h"

#include <QDebug>
#include "Logic.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Calculator c;
    c.setWindowTitle("Kalculator");

    c.show();

    return a.exec();
}
