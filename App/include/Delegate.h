#pragma once

#include "IDelegate.h"
#include "ILogic.h"
#include "Calculator.h"

#include <memory>

class Delegate : public IDelegate
{
public:
    Delegate(Calculator* = nullptr);

    QString getResult() const;

    void digitClicked(int) override;
    void dotClicked() override;
    void plusClicked() override;
    void minusClicked() override;
    void multClicked() override;
    void divClicked() override;
    void percentClicked() override;
    void equalClicked() override;
    void clearClicked() override;
    void cancelClicked() override;

private:
    std::pair<bool, double> calculate();
    void checkError();
    void clearAfterEqual();

    Calculator* m_calculatorPtr;

    QString m_result;
    bool m_isNeedToClear;

    std::unique_ptr<ILogic> m_logic;
};
