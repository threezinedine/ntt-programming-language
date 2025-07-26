#include <nttlang/tokenizer.h>

namespace ntt
{
    Tokenizer::Tokenizer(const std::string &code) : m_code(code)
    {
    }

    Tokenizer::~Tokenizer()
    {
        release_tokenes();
    }

    void Tokenizer::extract()
    {
        release_tokenes();

        m_tokens.push_back(new IntegerToken{
            TokenType::Integer,
            54,
        });
    }

    void Tokenizer::release_tokenes()
    {
        for (auto &token : m_tokens)
        {
            delete token;
        }
    }
} // namespace ntt
