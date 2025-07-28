#pragma once
#include "tokenizer.h"

namespace ntt
{
    /**
     * All of the possible categories of the AST node.
     */
    enum class ASTNodeType
    {
        Root,    ///< For each file, there is a root node.
        Float,   ///< For each number, there is a number node.
        Integer, ///< For each integer, there is a integer node.
        String,  ///< For each string, there is a string node.
    };

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
    };

    struct ASTNodeFloat : public ASTNode
    {
        float value; ///< The value of the current node.

        ASTNodeFloat(uint32_t start_position, uint32_t length, float value)
            : ASTNode(ASTNodeType::Float, start_position, length), value(value)
        {
        }
    };

    struct ASTNodeInteger : public ASTNode
    {
        int64_t value; ///< The value of the current node.

        ASTNodeInteger(uint32_t start_position, uint32_t length, int64_t value)
            : ASTNode(ASTNodeType::Integer, start_position, length), value(value)
        {
        }
    };

    struct ASTNodeString : public ASTNode
    {
        std::string value; ///< The value of the current node.

        ASTNodeString(uint32_t start_position, uint32_t length, std::string value)
            : ASTNode(ASTNodeType::String, start_position, length), value(value)
        {
        }
    };

    /**
     * Convert the tokens which are extracted from the tokenizer into the AST.
     */
    class Parser
    {
    public:
        Parser(const std::string &code);
        ~Parser();

        /**
         * Extracting the AST from the tokens which are extracted from the tokenizer.
         *
         * @return The root node of the AST. This pointer will be deleted by the destructor of the parser
         *      automatically, user does not need to delete it manually.
         */
        ASTNode *extract();

    private:
        Tokenizer m_tokenizer;
        ASTNode *m_root;
    };
} // namespace ntt

#define TYPE_TO_STRING(type) \
    [&]() -> std::string { \
        switch (type) \
        { \
        case TokenType::Float: \
            return "Float"; \
        case TokenType::Integer: \
            return "Integer"; \
        case TokenType::String: \
            return "String"; \
        default: \
            return "Unknown"; \
        } }()

#define TO_INTEGER_NODE(node) static_cast<ASTNodeInteger *>(node)
#define TO_FLOAT_NODE(node) static_cast<ASTNodeFloat *>(node)
#define TO_STRING_NODE(node) static_cast<ASTNodeString *>(node)