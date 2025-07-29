#pragma once
#include "base.h"
#include <string>

namespace ntt
{
    struct StringToken : public Token
    {
        std::string value; ///< The string value of this programming language

        StringToken(const std::string &value, const uint32_t &start_position, const uint32_t &length)
            : Token(TokenType::String, start_position, length), value(value) {}
    };
} // namespace ntt

#define TO_STRING_TOKEN(token) static_cast<::ntt::StringToken *>(token)
#define ASSERT_TOKEN_AS_STRING(token) ASSERT_TOKEN_TYPE(token, String)
