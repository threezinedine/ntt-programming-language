#pragma once
#include "types.h"
#include <cstdint>
#include "base.h"
#include <string>

namespace ntt
{
    struct ASTNodeString : public ASTNode
    {
        std::string value; ///< The value of the current node.

        ASTNodeString(uint32_t start_position, uint32_t length, std::string value)
            : ASTNode(ASTNodeType::String, start_position, length), value(value)
        {
        }

        ~ASTNodeString();
    };
};

#define TO_STRING_NODE(node) static_cast<::ntt::ASTNodeString *>(node)
