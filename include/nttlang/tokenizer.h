#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <memory>
#include <stdexcept>

namespace ntt
{
    /// @brief Store all possible way each word or character must be categorized
    enum class TokenType
    {
        Integer,     ///< Any integer number which contains negative sign
        Float,       ///< Any float number which contains negative sign
        String,      ///< Any string which is wrapped by double quotes or single quotes
        Identifier,  ///< Any identifier which is a sequence of letters, numbers, and underscores
        Keyword,     ///< Any keyword which is a sequence of letters, numbers, and underscores
        Parenthesis, ///< Any parenthesis which is a sequence of letters, numbers, and underscores
        Separator,   ///< Any separator which is a sequence of letters, numbers, and underscores
        Operator,    ///< Any operator which is a sequence of letters, numbers, and underscores

        InvalidIdentifier, ///< Any identifier which is not a valid identifier

        Unknown, ///< Any character which is not a valid token
    };

    /**
     * The base structure for all others tokens, If a new token type is added,
     *      it must be derived from this structure. The different attributes should
     *      be different from each other.
     */
    struct Token
    {
        /**
         * The attribute which is used for identifying the signature of the
         *      current token. This is the shared attribute between all tokens.
         */
        TokenType type;
        uint32_t start_position; ///< The index position inside the current code (the global one)
        uint32_t length;         ///< The length of the current token

        Token(TokenType type, const uint32_t &start_position, const uint32_t &length)
            : type(type), start_position(start_position), length(length)
        {
        }
    };

    struct IntegerToken : public Token
    {
        int32_t value; ///< The integer value of this programming language is 32-bit integer

        IntegerToken(int32_t value, const uint32_t &start_position, const uint32_t &length)
            : Token(TokenType::Integer, start_position, length), value(value)
        {
        }
    };

    struct FloatToken : public Token
    {
        float value; ///< The float value of this programming language is 32-bit float

        FloatToken(float value, const uint32_t &start_position, const uint32_t &length)
            : Token(TokenType::Float, start_position, length), value(value)
        {
        }
    };

    struct StringToken : public Token
    {
        std::string value; ///< The string value of this programming language

        StringToken(const std::string &value, const uint32_t &start_position, const uint32_t &length)
            : Token(TokenType::String, start_position, length), value(value) {}
    };

    struct IdentifierToken : public Token
    {
        std::string value; ///< The identifier value of this programming language

        IdentifierToken(const std::string &value, const uint32_t &start_position, const uint32_t &length)
            : Token(TokenType::Identifier, start_position, length), value(value) {}
    };

    struct KeywordToken : public Token
    {
        std::string value; ///< The keyword value of this programming language

        KeywordToken(const std::string &value, const uint32_t &start_position, const uint32_t &length)
            : Token(TokenType::Keyword, start_position, length), value(value) {}
    };

    struct InvalidIdentifierToken : public Token
    {
        std::string value; ///< The invalid identifier value of this programming language

        InvalidIdentifierToken(const std::string &value, const uint32_t &start_position, const uint32_t &length)
            : Token(TokenType::InvalidIdentifier, start_position, length), value(value) {}
    };

    struct ParenthesisToken : public Token
    {
        std::string value; ///< The parenthesis value of this programming language

        ParenthesisToken(const std::string &value, const uint32_t &start_position, const uint32_t &length)
            : Token(TokenType::Parenthesis, start_position, length), value(value) {}
    };

    struct SeparatorToken : public Token
    {
        std::string value; ///< The separator value of this programming language

        SeparatorToken(const std::string &value, const uint32_t &start_position, const uint32_t &length)
            : Token(TokenType::Separator, start_position, length), value(value) {}
    };

    struct OperatorToken : public Token
    {
        std::string value; ///< The operator value of this programming language

        OperatorToken(const std::string &value, const uint32_t &start_position, const uint32_t &length)
            : Token(TokenType::Operator, start_position, length), value(value) {}
    };

    struct UnknownToken : public Token
    {
        std::string value; ///< The character value of this programming language

        UnknownToken(const std::string &value, uint32_t start_position, uint32_t length)
            : Token(TokenType::Unknown, start_position, length), value(value) {}
    };

    /**
     * The only task of this class is trying to search through the whole code
     *      and try to identify the token.
     */
    class Tokenizer
    {
    public:
        Tokenizer(const std::string &code);
        ~Tokenizer();

        /**
         * Internal scan over the whole code and try to identify the token.
         */
        void extract();

        /**
         * Get the number of the tokens which has been identified.
         */
        inline uint32_t get_token_count() const { return m_tokens.size(); }

        /**
         * Get the token at the specific index.
         */
        inline Token *&get_token(uint32_t index) { return m_tokens[index]; }

    private:
        /**
         * Used for cleaning the memory of the tokens, this function should be called every time the
         *      tokenizer content has been changed.
         */
        void release_tokenes();

    private:
        std::string m_code;
        std::vector<Token *> m_tokens;
    };
} // namespace ntt

#ifdef DEBUG
#define ASSERT_TOKEN_TYPE(token, expectedType)           \
    if (token->type != ::ntt::TokenType::expectedType)   \
    {                                                    \
        throw std::runtime_error("Token type mismatch"); \
    }
#else
#define ASSERT_TOKEN_TYPE(token, expectedType)
#endif

#define ASSERT_TOKEN_AS_INTEGER(token) ASSERT_TOKEN_TYPE(token, Integer)
#define ASSERT_TOKEN_AS_FLOAT(token) ASSERT_TOKEN_TYPE(token, Float)
#define ASSERT_TOKEN_AS_STRING(token) ASSERT_TOKEN_TYPE(token, String)
#define ASSERT_TOKEN_AS_IDENTIFIER(token) ASSERT_TOKEN_TYPE(token, Identifier)
#define ASSERT_TOKEN_AS_KEYWORD(token) ASSERT_TOKEN_TYPE(token, Keyword)
#define ASSERT_TOKEN_AS_INVALID_IDENTIFIER(token) ASSERT_TOKEN_TYPE(token, InvalidIdentifier)
#define ASSERT_TOKEN_AS_PARENTHESIS(token) ASSERT_TOKEN_TYPE(token, Parenthesis)
#define ASSERT_TOKEN_AS_SEPARATOR(token) ASSERT_TOKEN_TYPE(token, Separator)
#define ASSERT_TOKEN_AS_OPERATOR(token) ASSERT_TOKEN_TYPE(token, Operator)
#define ASSERT_TOKEN_AS_UNKNOWN(token) ASSERT_TOKEN_TYPE(token, Unknown)

#define TO_INTEGER(token) static_cast<::ntt::IntegerToken *>(token)
#define TO_FLOAT(token) static_cast<::ntt::FloatToken *>(token)
#define TO_STRING(token) static_cast<::ntt::StringToken *>(token)
#define TO_IDENTIFIER(token) static_cast<::ntt::IdentifierToken *>(token)
#define TO_KEYWORD(token) static_cast<::ntt::KeywordToken *>(token)
#define TO_INVALID_IDENTIFIER(token) static_cast<::ntt::InvalidIdentifierToken *>(token)
#define TO_PARENTHESIS(token) static_cast<::ntt::ParenthesisToken *>(token)
#define TO_SEPARATOR(token) static_cast<::ntt::SeparatorToken *>(token)
#define TO_OPERATOR(token) static_cast<::ntt::OperatorToken *>(token)
#define TO_UNKNOWN(token) static_cast<::ntt::UnknownToken *>(token)