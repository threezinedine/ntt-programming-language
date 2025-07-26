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
        Float,   ///< Any float number which contains negative sign
        String,  ///< Any string which is wrapped by double quotes or single quotes
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

        Token(TokenType type) : type(type) {}
    };

    struct IntegerToken : public Token
    {
        int32_t value; ///< The integer value of this programming language is 32-bit integer

        IntegerToken(int32_t value) : Token(TokenType::Integer), value(value) {}
    };

    struct FloatToken : public Token
    {
        float value; ///< The float value of this programming language is 32-bit float

        FloatToken(float value) : Token(TokenType::Float), value(value) {}
    };

    struct StringToken : public Token
    {
        std::string value; ///< The string value of this programming language

        StringToken(const std::string &value) : Token(TokenType::String), value(value) {}
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

        /**
         * Get the number of the tokens which has been identified.
         */
        inline uint32_t get_token_count() const { return m_tokens.size(); }

        /**
         * Get the token at the specific index.
         */
        inline Token *&get_token(uint32_t index) { return m_tokens[index]; }

    private:
        /**
         * Used for cleaning the memory of the tokens, this function should be called every time the
         *      tokenizer content has been changed.
         */
        void release_tokenes();

    private:
        std::string m_code;
        std::vector<Token *> m_tokens;
    };
} // namespace ntt

#define TO_INTEGER(token) static_cast<::ntt::IntegerToken *>(token)
#define TO_FLOAT(token) static_cast<::ntt::FloatToken *>(token)
#define TO_STRING(token) static_cast<::ntt::StringToken *>(token)
