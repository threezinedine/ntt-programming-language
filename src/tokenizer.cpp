#include <nttlang/tokenizer.h>
#include <string>
#include <vector>
#include <regex>
#include <functional>
#include <nttlang/macros.h>

namespace ntt
{
    typedef std::function<Token *(const std::smatch &, std::string &, const uint32_t &)> TokenCallback;

    /**
     * The the store information about the token syntax checking.
     */
    struct TokenSyntaxRule
    {
        std::string regex;      ///< If the input string matches this regex, the token will has the type as the type of this rule
        TokenCallback callback; ///< The function which will be used to create the token
    };

    static TokenCallback s_string_token_callback = [](const std::smatch &match, std::string &tempCode, const uint32_t &offset) -> Token *
    {
        NTT_UNUSED(tempCode);
        return new StringToken(match[0].str().substr(1, match[0].str().size() - 2), offset, match[0].str().size());
    };

    static bool is_character(char c)
    {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    static const std::string keyword_chains = "(if|else|elseif|for|while|let|const)";

    static std::vector<TokenSyntaxRule> s_token_syntax_rules = {
        // keywords
        {
            "(^" + keyword_chains + "[{()};\\s])|(^" + keyword_chains + "$)",
            [](const std::smatch &match, std::string &tempCode, const uint32_t &offset) -> Token *
            {
                const std::string &keyword = match[0].str();
                if (is_character(keyword[keyword.size() - 1]))
                {
                    return new KeywordToken(keyword, offset, keyword.size());
                }
                else
                {
                    tempCode = keyword[keyword.size() - 1] + tempCode;
                    return new KeywordToken(keyword.substr(0, keyword.size() - 1), offset, keyword.size() - 1);
                }
            },
        },

        // parenthesis
        {
            R"(^[\(\{\[\]\}\)])",
            [](const std::smatch &match, std::string &tempCode, const uint32_t &offset) -> Token *
            {
                NTT_UNUSED(tempCode);
                const uint32_t length = match[0].str().size();
                return new ParenthesisToken(match[0].str(), offset, length);
            },
        },

        // invalid identifier
        {
            R"(^[0-9]+[a-eg-zA-EG-Z_]+[\S]*)",
            [](const std::smatch &match, std::string &tempCode, const uint32_t &offset) -> Token *
            {
                NTT_UNUSED(tempCode);
                const uint32_t length = match[0].str().size();
                return new InvalidIdentifierToken(match[0].str(), offset, length);
            },
        },
        {
            R"(^[a-zA-Z_][a-zA-Z0-9_]*)",
            [](const std::smatch &match, std::string &tempCode, const uint32_t &offset) -> Token *
            {
                NTT_UNUSED(tempCode);
                const uint32_t length = match[0].str().size();
                return new IdentifierToken(match[0].str(), offset, length);
            },
        },
        {
            R"(^(-?[0-9]*\.[0-9]+f?|-?[0-9]*f))",
            [](const std::smatch &match, std::string &tempCode, const uint32_t &offset) -> Token *
            {
                NTT_UNUSED(tempCode);
                const uint32_t length = match[0].str().size();
                return new FloatToken(std::stof(match[0].str()), offset, length);
            },
        },
        {
            R"(^-?[0-9]+)",
            [](const std::smatch &match, std::string &tempCode, const uint32_t &offset) -> Token *
            {
                NTT_UNUSED(tempCode);
                const uint32_t length = match[0].str().size();
                return new IntegerToken(std::stoi(match[0].str()), offset, length);
            },
        },
        // operators
        {
            R"(^[!=+\-*/%<>]{1,2})",
            [](const std::smatch &match, std::string &tempCode, const uint32_t &offset) -> Token *
            {
                NTT_UNUSED(tempCode);
                const uint32_t length = match[0].str().size();
                return new OperatorToken(match[0].str(), offset, length);
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
        {
            R"(^[;,])",
            [](const std::smatch &match, std::string &tempCode, const uint32_t &offset) -> Token *
            {
                NTT_UNUSED(tempCode);
                return new SeparatorToken(match[0].str(), offset, match[0].str().size());
            },
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
                std::regex regex("^[\\s\\n]+");
                std::smatch match;
#ifdef MSVC
                std::string currentTempString = '\n' + tempCode;
                if (std::regex_search(currentTempString, match, regex))
#else
                if (std::regex_search(tempCode, match, regex))
#endif
                {
                    tempCode = tempCode.substr(match.position() + match.length()
#ifdef MSVC
                        - 1
#endif
                    );
                }
            }

            uint32_t offset = 0;

            for (auto &rule : s_token_syntax_rules)
            {
                std::regex regex(rule.regex);
                std::smatch match;
                const std::string currentTempString = tempCode;

				offset = m_code.length() - tempCode.length();
                if (std::regex_search(currentTempString, match, regex))
                {
                    is_matched = true;
                    tempCode = tempCode.substr(match.position() + match.length());
                    m_tokens.push_back(rule.callback(match, tempCode, offset));
                    break;
                }
            }

            if (!is_matched)
            {
                m_tokens.push_back(new UnknownToken(std::string(1, tempCode[0]), offset, 1));
                offset += 1;
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
