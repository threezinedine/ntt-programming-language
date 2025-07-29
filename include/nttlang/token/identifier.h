#pragma once
#include "base.h"
#include <string>

namespace ntt
{
    struct IdentifierToken : public Token
    {
        std::string value; ///< The identifier value of this programming language

        IdentifierToken(const std::string &value, const uint32_t &start_position, const uint32_t &length)
            : Token(TokenType::Identifier, start_position, length), value(value) {}
    };

} // namespace ntt

#define TO_IDENTIFIER_TOKEN(token) static_cast<::ntt::IdentifierToken *>(token)
#define ASSERT_TOKEN_AS_IDENTIFIER(token) ASSERT_TOKEN_TYPE(token, Identifier)
