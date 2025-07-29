#pragma once
#include "types.h"
#include <cstdint>

namespace ntt
{
    /**
     * The base structure for all others tokens, If a new token type is added,
     *      it must be derived from this structure. The different attributes should
     *      be different from each other.
     */
    struct Token
    {
        /**
         * The attribute which is used for identifying the signature of the
         *      current token. This is the shared attribute between all tokens.
         */
        TokenType type;
        uint32_t start_position; ///< The index position inside the current code (the global one)
        uint32_t length;         ///< The length of the current token

        Token(TokenType type, const uint32_t &start_position, const uint32_t &length)
            : type(type), start_position(start_position), length(length)
        {
        }
    };

} // namespace ntt

#ifdef DEBUG
#define ASSERT_TOKEN_TYPE(token, expectedType)           \
    if (token->type != ::ntt::TokenType::expectedType)   \
    {                                                    \
        throw std::runtime_error("Token type mismatch"); \
    }
#else
#define ASSERT_TOKEN_TYPE(token, expectedType)
#endif
