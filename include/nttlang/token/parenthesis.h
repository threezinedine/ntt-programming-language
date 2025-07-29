#pragma once
#include "base.h"
#include <string>

namespace ntt
{
    struct ParenthesisToken : public Token
    {
        std::string value; ///< The parenthesis value of this programming language

        ParenthesisToken(const std::string &value, const uint32_t &start_position, const uint32_t &length)
            : Token(TokenType::Parenthesis, start_position, length), value(value) {}
    };
} // namespace ntt

#define TO_PARENTHESIS_TOKEN(token) static_cast<::ntt::ParenthesisToken *>(token)
#define ASSERT_TOKEN_AS_PARENTHESIS(token) ASSERT_TOKEN_TYPE(token, Parenthesis)
