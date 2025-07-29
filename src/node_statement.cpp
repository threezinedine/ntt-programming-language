#include "nttlang/nodes/statement.h"

namespace ntt
{
    ASTNodeStatement::~ASTNodeStatement()
    {
        delete expression;
    }
} // namespace ntt