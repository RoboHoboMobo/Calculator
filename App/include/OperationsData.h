#pragma once

struct OperationsData
{
    enum Type {
        Operand = 0,
        Operator
    };

    enum Operator {
        None = 0,
        Plus,
        Minus,
        Mult,
        Div
    };

    explicit OperationsData(double operand);
    explicit OperationsData(enum Operator);

    Type m_type;
    double m_operand;
    enum Operator m_operator;
};
