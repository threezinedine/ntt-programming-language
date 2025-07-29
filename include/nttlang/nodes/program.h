#pragma once
#include <vector>
#include "base.h"
#include "statement.h"

namespace ntt
{
    struct ASTNodeProgram : public ASTNode
    {
        std::vector<ASTNodeStatement *> statements; ///< The statements of the current node.

        ASTNodeProgram(uint32_t start_position, uint32_t length)
            : ASTNode(ASTNodeType::Program, start_position, length)
        {
        }

        ~ASTNodeProgram();
    };

} // namespace ntt

#define TO_PROGRAM_NODE(node) static_cast<::ntt::ASTNodeProgram *>(node)
