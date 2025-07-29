#pragma once
#include "types.h"
#include "base.h"
#include <cstdint>

namespace ntt
{
    struct ASTNodeFloat : public ASTNode
    {
        float value; ///< The value of the current node.

        ASTNodeFloat(uint32_t start_position, uint32_t length, float value)
            : ASTNode(ASTNodeType::Float, start_position, length), value(value)
        {
        }

        ~ASTNodeFloat();
    };
} // namespace ntt

#define TO_FLOAT_NODE(node) static_cast<::ntt::ASTNodeFloat *>(node)