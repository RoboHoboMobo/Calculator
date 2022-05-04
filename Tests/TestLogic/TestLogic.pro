QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

prefix = $$PWD/../../App

INCLUDEPATH += $$prefix/include

SOURCES += tst_logic.cpp \
    $$prefix/src/Logic.cpp \
    $$prefix/src/OperationsData.cpp \
    $$prefix/src/CalculationFrame.cpp

HEADERS += $$prefix/include/Logic.h \
    $$prefix/include/OperationsData.h \
    $$prefix/src/CalculationFrame.h
