#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include "token/token.h"

namespace ntt
{
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