#pragma once
#include "base.h"

namespace ntt
{
    struct ASTNodeStatement : public ASTNode
    {
        ASTNode *expression; ///< The expression of the current node.

        ASTNodeStatement(uint32_t start_position, uint32_t length)
            : ASTNode(ASTNodeType::Statement, start_position, length)
        {
        }

        ~ASTNodeStatement();
    };
} // namespace ntt

#define TO_STATEMENT_NODE(node) static_cast<::ntt::ASTNodeStatement *>(node)
