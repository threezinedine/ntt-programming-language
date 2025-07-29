#pragma once
#include "base.h"
#include <string>

namespace ntt
{
    struct KeywordToken : public Token
    {
        std::string value; ///< The keyword value of this programming language

        KeywordToken(const std::string &value, const uint32_t &start_position, const uint32_t &length)
            : Token(TokenType::Keyword, start_position, length), value(value) {}
    };
} // namespace ntt

#define TO_KEYWORD_TOKEN(token) static_cast<::ntt::KeywordToken *>(token)
