#include "nttlang/nodes/program.h"

namespace ntt
{
    ASTNodeProgram::~ASTNodeProgram()
    {
        for (auto statement : statements)
        {
            delete statement;
        }
    }
} // namespace ntt