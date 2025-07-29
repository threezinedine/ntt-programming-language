#pragma once
#include "base.h"
#include <string>

namespace ntt
{
    struct InvalidIdentifierToken : public Token
    {
        std::string value; ///< The invalid identifier value of this programming language

        InvalidIdentifierToken(const std::string &value, const uint32_t &start_position, const uint32_t &length)
            : Token(TokenType::InvalidIdentifier, start_position, length), value(value) {}
    };
} // namespace ntt

#define TO_INVALID_IDENTIFIER_TOKEN(token) static_cast<::ntt::InvalidIdentifierToken *>(token)
#define ASSERT_TOKEN_AS_INVALID_IDENTIFIER(token) ASSERT_TOKEN_TYPE(token, InvalidIdentifier)
