#pragma once
#include "tokenizer.h"
#include "nodes/nodes.h"

namespace ntt
{
    /**
     * Convert the tokens which are extracted from the tokenizer into the AST.
     */
    class Parser
    {
    public:
        Parser(const std::string &code);
        ~Parser();

        /**
         * Extracting the AST from the tokens which are extracted from the tokenizer.
         *
         * @return The root node of the AST. This pointer will be deleted by the destructor of the parser
         *      automatically, user does not need to delete it manually.
         */
        ASTNode *extract();

    private:
        Tokenizer m_tokenizer;
        ASTNode *m_root;
    };
} // namespace ntt
