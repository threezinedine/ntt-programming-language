#pragma once
#include "types.h"
#include <cstdint>

namespace ntt
{
    /**
     * Based structure which stores the information of the AST node.
     */
    struct ASTNode
    {
        ASTNodeType type;        ///< The type of the current node.
        uint32_t start_position; ///< The start position of the current node.
        uint32_t length;         ///< The length of the current node.

        ASTNode(ASTNodeType type, uint32_t start_position, uint32_t length)
            : type(type), start_position(start_position), length(length)
        {
        }

        virtual ~ASTNode() = default;
    };
} // namespace ntt
