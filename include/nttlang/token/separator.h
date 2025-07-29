#pragma once
#include "base.h"
#include <string>

namespace ntt
{
    struct SeparatorToken : public Token
    {
        std::string value; ///< The separator value of this programming language

        SeparatorToken(const std::string &value, const uint32_t &start_position, const uint32_t &length)
            : Token(TokenType::Separator, start_position, length), value(value) {}
    };
} // namespace ntt

#define TO_SEPARATOR_TOKEN(token) static_cast<::ntt::SeparatorToken *>(token)
#define ASSERT_TOKEN_AS_SEPARATOR(token) ASSERT_TOKEN_TYPE(token, Separator)
