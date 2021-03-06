QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14 c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/include

SOURCES += \
    main.cpp \
    src/Button.cpp \
    src/CalculationFrame.cpp \
    src/Calculator.cpp \
    src/Delegate.cpp \
    src/Logic.cpp \
    src/OperationsData.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    include/Button.h \
    include/CalculationFrame.h \
    include/Calculator.h \
    include/Delegate.h \
    include/IDelegate.h \
    include/ILogic.h \
    include/Logic.h \
    include/OperationsData.h
