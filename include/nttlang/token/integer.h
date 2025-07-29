#pragma once
#include "base.h"
#include <cstdint>

namespace ntt
{
    struct IntegerToken : public Token
    {
        int32_t value; ///< The integer value of this programming language is 32-bit integer

        IntegerToken(int32_t value, const uint32_t &start_position, const uint32_t &length)
            : Token(TokenType::Integer, start_position, length), value(value)
        {
        }
    };

} // namespace ntt

#define TO_INTEGER_TOKEN(token) static_cast<::ntt::IntegerToken *>(token)
#define ASSERT_TOKEN_AS_INTEGER(token) ASSERT_TOKEN_TYPE(token, Integer)
