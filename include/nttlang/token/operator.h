#pragma once
#include "base.h"
#include <string>

namespace ntt
{
    struct OperatorToken : public Token
    {
        std::string value; ///< The operator value of this programming language

        OperatorToken(const std::string &value, const uint32_t &start_position, const uint32_t &length)
            : Token(TokenType::Operator, start_position, length), value(value) {}
    };
} // namespace ntt

#define TO_OPERATOR_TOKEN(token) static_cast<::ntt::OperatorToken *>(token)
#define ASSERT_TOKEN_AS_OPERATOR(token) ASSERT_TOKEN_TYPE(token, Operator)
