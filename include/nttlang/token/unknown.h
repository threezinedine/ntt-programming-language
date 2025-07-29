#pragma once
#include "base.h"
#include <string>

namespace ntt
{
    struct UnknownToken : public Token
    {
        std::string value; ///< The character value of this programming language

        UnknownToken(const std::string &value, uint32_t start_position, uint32_t length)
            : Token(TokenType::Unknown, start_position, length), value(value) {}
    };
} // namespace ntt

#define TO_UNKNOWN_TOKEN(token) static_cast<::ntt::UnknownToken *>(token)
#define ASSERT_TOKEN_AS_UNKNOWN(token) ASSERT_TOKEN_TYPE(token, Unknown)
