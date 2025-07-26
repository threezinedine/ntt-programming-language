#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <memory>

namespace ntt
{
    /// @brief Store all possible way each word or character must be categorized
    enum class TokenType
    {
        Integer, ///< Any integer number which contains negative sign
    };

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
    };

    struct IntegerToken : public Token
    {
        int32_t value; ///< The integer value of this programming language is 32-bit integer
    };

    /**
     * The only task of this class is trying to search through the whole code
     *      and try to identify the token.
     */
    class Tokenizer
    {
    public:
        Tokenizer(const std::string &code);
        ~Tokenizer();

        /**
         * Internal scan over the whole code and try to identify the token.
         */
        void extract();

        inline uint32_t get_token_count() const { return m_tokens.size(); }
        inline Token *&get_token(uint32_t index) { return m_tokens[index]; }

    private:
        void release_tokenes();

    private:
        std::string m_code;
        std::vector<Token *> m_tokens;
    };
} // namespace ntt

#define TO_NUMBER(token) static_cast<::ntt::IntegerToken *>(token)
