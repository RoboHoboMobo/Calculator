QT += testlib core gui widgets

CONFIG += qt console warn_on depend_includepath testcase

prefix = $$PWD/../../App

INCLUDEPATH += $$prefix/include

SOURCES += tst_delegate.cpp \
    $$prefix/src/Delegate.cpp \
    $$prefix/src/Button.cpp \
    $$prefix/src/OperationsData.cpp \
    MockCalculationFrame.cpp \
    MockCalculator.cpp \
    MockLogic.cpp

HEADERS += $$prefix/include/Delegate.h \
    $$prefix/include/IDelegate.h \
    $$prefix/include/Button.h \
    $$prefix/include/OperationsData.h \
    $$prefix/include/CalculationFrame.h \
    $$prefix/include/ILogic.h \
    $$prefix/include/Logic.h \
    $$prefix/include/Calculator.h \
    MockLogic.h
