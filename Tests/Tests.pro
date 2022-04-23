QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

# TEMPLATE = app

prefix = $$PWD/../App

INCLUDEPATH += $$prefix/include

SOURCES +=  tst_testlogic.cpp \
    $$prefix/src/Logic.cpp

HEADERS += $$prefix/include/Logic.h
