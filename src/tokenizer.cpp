#include <nttlang/tokenizer.h>
#include <string>
#include <vector>
#include <regex>
#include <functional>

namespace ntt
{
    typedef std::function<Token *(const std::smatch &)> TokenCallback;

    /**
     * The the store information about the token syntax checking.
     */
    struct TokenSyntaxRule
    {
        std::string regex;      ///< If the input string matches this regex, the token will has the type as the type of this rule
        TokenCallback callback; ///< The function which will be used to create the token
    };

    static TokenCallback s_string_token_callback = [](const std::smatch &match) -> Token *
    {
        return new StringToken(match[0].str().substr(1, match[0].str().size() - 2));
    };

    static std::vector<TokenSyntaxRule> s_token_syntax_rules = {
        {
            R"(^(-?[0-9]*\.[0-9]+f?|-?[0-9]*f))",
            [](const std::smatch &match) -> Token *
            {
                return new FloatToken(std::stof(match[0].str()));
            },
        },
        {
            R"(^-?[0-9]+)",
            [](const std::smatch &match) -> Token *
            {
                return new IntegerToken(std::stoi(match[0].str()));
            },
        },
        {
            R"(^'[\s\S]*')",
            s_string_token_callback,
        },
        {
            R"(^"[\s\S]*|\\\"|[^"]")",
            s_string_token_callback,
        },
    };

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

        /**
         * used for storing the string which is processed, during the
         *      the processing time, the original string will not be modified.
         */
        std::string tempCode = m_code;

        while (!tempCode.empty())
        {
            bool is_matched = false;

            // remove spaces to the next token
            {
                std::regex regex(R"(^[\s\n]+)");
                std::smatch match;
                if (std::regex_search(tempCode, match, regex))
                {
                    tempCode = tempCode.substr(match.position() + match.length());
                }
            }

            for (auto &rule : s_token_syntax_rules)
            {
                std::regex regex(rule.regex);
                std::smatch match;
                if (std::regex_search(tempCode, match, regex))
                {
                    is_matched = true;
                    m_tokens.push_back(rule.callback(match));
                    tempCode = tempCode.substr(match.position() + match.length());
                    break;
                }
            }

            if (!is_matched)
            {
                m_tokens.push_back(new UnknownToken(tempCode[0]));
                tempCode = tempCode.substr(1);
            }
        }
    }

    void Tokenizer::release_tokenes()
    {
        for (auto &token : m_tokens)
        {
            delete token;
        }
    }
} // namespace ntt
