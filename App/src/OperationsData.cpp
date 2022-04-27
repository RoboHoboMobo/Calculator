#include "OperationsData.h"

OperationsData::OperationsData(double op)
    : m_type{Type::Operand}
    , m_operand{op}
    , m_operator{}
{
}

OperationsData::OperationsData(enum Operator op)
    : m_type{Type::Operator}
    , m_operand{0.0}
    , m_operator{op}
{
}
