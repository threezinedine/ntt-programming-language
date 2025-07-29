#pragma once

namespace ntt
{
    /**
     * All of the possible categories of the AST node.
     */
    enum class ASTNodeType
    {
        Float,     ///< For each number, there is a number node.
        Integer,   ///< For each integer, there is a integer node.
        String,    ///< For each string, there is a string node.
        Statement, ///< For each statement, there is a statement node.
        Program,   ///< For each program, there is a program node.
    };

} // namespace ntt

#define AST_NODE_TYPE_TO_STRING(type) \
    [&]() -> std::string { \
        switch (type) \
        { \
        case ::ntt::ASTNodeType::Float: \
            return "Float"; \
        case ::ntt::ASTNodeType::Integer: \
            return "Integer"; \
        case ::ntt::ASTNodeType::String: \
            return "String"; \
        case ::ntt::ASTNodeType::Statement: \
            return "Statement"; \
        case ::ntt::ASTNodeType::Program: \
            return "Program"; \
        default: \
            return "Unknown"; \
        } }()
