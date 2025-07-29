#pragma once
#include "types.h"
#include <cstdint>
#include "base.h"

namespace ntt
{
    struct ASTNodeInteger : public ASTNode
    {
        int64_t value; ///< The value of the current node.

        ASTNodeInteger(uint32_t start_position, uint32_t length, int64_t value)
            : ASTNode(ASTNodeType::Integer, start_position, length), value(value)
        {
        }

        ~ASTNodeInteger();
    };
} // namespace ntt

#define TO_INTEGER_NODE(node) static_cast<::ntt::ASTNodeInteger *>(node)