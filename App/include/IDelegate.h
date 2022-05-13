#pragma once

#include <QObject>

class IDelegate : public QObject
{
    Q_OBJECT

public slots:
    virtual void digitClicked(int) = 0;
    virtual void dotClicked() = 0;
    virtual void plusClicked() = 0;
    virtual void minusClicked() = 0;
    virtual void multClicked() = 0;
    virtual void divClicked() = 0;
    virtual void percentClicked() = 0;
    virtual void equalClicked() = 0;
    virtual void clearClicked() = 0;
    virtual void cancelClicked() = 0;

signals:
    void passResultString(const QString& result);
};
