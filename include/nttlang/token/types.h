#pragma once

namespace ntt
{
    /// @brief Store all possible way each word or character must be categorized
    enum class TokenType
    {
        Integer,     ///< Any integer number which contains negative sign
        Float,       ///< Any float number which contains negative sign
        String,      ///< Any string which is wrapped by double quotes or single quotes
        Identifier,  ///< Any identifier which is a sequence of letters, numbers, and underscores
        Keyword,     ///< Any keyword which is a sequence of letters, numbers, and underscores
        Parenthesis, ///< Any parenthesis which is a sequence of letters, numbers, and underscores
        Separator,   ///< Any separator which is a sequence of letters, numbers, and underscores
        Operator,    ///< Any operator which is a sequence of letters, numbers, and underscores

        InvalidIdentifier, ///< Any identifier which is not a valid identifier

        Unknown, ///< Any character which is not a valid token
    };
} // namespace ntt

#define TOKEN_TYPE_TO_STRING(type) \
    [&]() -> std::string { \
        switch (type) \
        { \
        case ::ntt::TokenType::Integer: \
            return "Integer"; \
        case ::ntt::TokenType::Float: \
            return "Float"; \
        case ::ntt::TokenType::String: \
            return "String"; \
        case ::ntt::TokenType::Identifier: \
            return "Identifier"; \
        case ::ntt::TokenType::Keyword: \
            return "Keyword"; \
        case ::ntt::TokenType::Parenthesis: \
            return "Parenthesis"; \
        case ::ntt::TokenType::Separator: \
            return "Separator"; \
        case ::ntt::TokenType::Operator: \
            return "Operator"; \
        case ::ntt::TokenType::InvalidIdentifier: \
            return "InvalidIdentifier"; \
        case ::ntt::TokenType::Unknown: \
            return "Unknown"; \
        default: \
            return "Unknown Token Type"; \
        } }()
