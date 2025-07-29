#include "nttlang/parser.h"
#include "nttlang/nodes/nodes.h"

namespace ntt
{

    ASTNodeStatement::~ASTNodeStatement()
    {
        delete expression;
    }

    ASTNodeProgram::~ASTNodeProgram()
    {
        for (auto statement : statements)
        {
            delete statement;
        }
    }

    Parser::Parser(const std::string &code) : m_tokenizer(code), m_root(nullptr)
    {
    }

    Parser::~Parser()
    {
        if (m_root)
        {
            delete m_root;
        }
    }

    ASTNode *Parser::extract()
    {
        m_tokenizer.extract();

        if (m_tokenizer.get_token_count() == 0)
        {
            m_root = new ASTNodeProgram(0, 0);
            return m_root;
        }

        switch (m_tokenizer.get_token(0)->type)
        {
        case TokenType::Float:
            m_root = new ASTNodeFloat(m_tokenizer.get_token(0)->start_position,
                                      m_tokenizer.get_token(0)->length,
                                      TO_FLOAT(m_tokenizer.get_token(0))->value);
            break;
        case TokenType::Integer:
            m_root = new ASTNodeInteger(m_tokenizer.get_token(0)->start_position,
                                        m_tokenizer.get_token(0)->length,
                                        TO_INTEGER(m_tokenizer.get_token(0))->value);
            break;
        case TokenType::String:
            m_root = new ASTNodeString(m_tokenizer.get_token(0)->start_position,
                                       m_tokenizer.get_token(0)->length,
                                       TO_STRING(m_tokenizer.get_token(0))->value);
            break;
        default:
            throw std::runtime_error("Not implemented type: " + TOKEN_TYPE_TO_STRING(m_tokenizer.get_token(0)->type));
        }

        return m_root;
    }
} // namespace ntt
