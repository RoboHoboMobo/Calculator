QT += testlib core gui widgets

CONFIG += qt console warn_on depend_includepath testcase

prefix = $$PWD/../../App

INCLUDEPATH += $$prefix/include

SOURCES += tst_calculator.cpp \
    $$prefix/src/Calculator.cpp \
    $$prefix/src/Button.cpp \
    $$prefix/src/OperationsData.cpp \
    MocCalculationFrame.cpp \
    MocLogic.cpp

HEADERS += $$prefix/include/Calculator.h \
    $$prefix/include/Button.h \
    $$prefix/include/OperationsData.h \
    $$prefix/include/CalculationFrame.h \
    $$prefix/include/ILogic.h \
    $$prefix/include/Logic.h

