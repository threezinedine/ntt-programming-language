#pragma once
#include "base.h"

namespace ntt
{
    struct FloatToken : public Token
    {
        float value; ///< The float value of this programming language is 32-bit float

        FloatToken(float value, const uint32_t &start_position, const uint32_t &length)
            : Token(TokenType::Float, start_position, length), value(value)
        {
        }
    };
} // namespace ntt

#define TO_FLOAT_TOKEN(token) static_cast<::ntt::FloatToken *>(token)
#define ASSERT_TOKEN_AS_FLOAT(token) ASSERT_TOKEN_TYPE(token, Float)
