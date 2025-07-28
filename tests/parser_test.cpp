#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "nttlang/parser.h"

using namespace ntt;
using namespace ::testing;

#define DEFINE_TOKEN(code) \
    Parser parser(code);   \
    ASTNode *root = parser.extract()

#define EXPECT_AST_NODE_TYPE(node, expectedType) EXPECT_EQ(node->type, expectedType)
#define EXPECT_AST_NODE_START_POSITION(node, expectedStartPosition) EXPECT_EQ(node->start_position, expectedStartPosition)
#define EXPECT_AST_NODE_LENGTH(node, expectedLength) EXPECT_EQ(node->length, expectedLength)
#define EXPECT_AST_NODE_VALUE(node, expectedValue) EXPECT_EQ(node->value, expectedValue)

#define EXPECT_INTEGER_NODE_VALUE(node, expectedValue) \
    EXPECT_EQ(node->type, ASTNodeType::Integer);       \
    EXPECT_EQ(TO_INTEGER_NODE(node)->value, expectedValue)

#define EXPECT_FLOAT_NODE_VALUE(node, expectedValue) \
    EXPECT_EQ(node->type, ASTNodeType::Float);       \
    EXPECT_THAT(TO_FLOAT_NODE(node)->value, FloatEq(expectedValue))

#define EXPECT_STRING_NODE_VALUE(node, expectedValue) \
    EXPECT_EQ(node->type, ASTNodeType::String);       \
    EXPECT_THAT(TO_STRING_NODE(node)->value, StrEq(expectedValue))

TEST(Parser, extract_number)
{
    DEFINE_TOKEN("54");
    EXPECT_AST_NODE_START_POSITION(root, 0);
    EXPECT_AST_NODE_LENGTH(root, 2);
    EXPECT_INTEGER_NODE_VALUE(root, 54);
}

TEST(Parser, extract_float)
{
    DEFINE_TOKEN("54.12");
    EXPECT_AST_NODE_START_POSITION(root, 0);
    EXPECT_AST_NODE_LENGTH(root, 5);
    EXPECT_FLOAT_NODE_VALUE(root, 54.12);
}

TEST(Parser, extract_string)
{
    DEFINE_TOKEN(R"("Hello, World!")");
    EXPECT_AST_NODE_START_POSITION(root, 0);
    EXPECT_AST_NODE_LENGTH(root, 15);
    EXPECT_STRING_NODE_VALUE(root, "Hello, World!");
}
