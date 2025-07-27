#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <nttlang/tokenizer.h>

using namespace ntt;

#define DEFINE_TOKEN(content)     \
    Tokenizer tokenizer(content); \
    tokenizer.extract()

#define EXPECT_TOKEN_COUNT(count) EXPECT_THAT(tokenizer.get_token_count(), count)
#define EXPECT_TOKEN_TYPE(index, expectedType) EXPECT_THAT(tokenizer.get_token(index)->type, TokenType::expectedType)

#define EXPECT_TOKEN_INTEGER(index, expectedValue) \
    EXPECT_TOKEN_TYPE(index, Integer);             \
    EXPECT_THAT(TO_INTEGER(tokenizer.get_token(index))->value, expectedValue)
#define EXPECT_TOKEN_FLOAT(index, expectedValue) \
    EXPECT_TOKEN_TYPE(index, Float);             \
    EXPECT_THAT(TO_FLOAT(tokenizer.get_token(index))->value, expectedValue)
#define EXPECT_TOKEN_STRING(index, expectedValue) \
    EXPECT_TOKEN_TYPE(index, String);             \
    EXPECT_THAT(TO_STRING(tokenizer.get_token(index))->value, expectedValue)
#define EXPECT_TOKEN_IDENTIFIER(index, expectedValue) \
    EXPECT_TOKEN_TYPE(index, Identifier);             \
    EXPECT_THAT(TO_IDENTIFIER(tokenizer.get_token(index))->value, expectedValue)
#define EXPECT_TOKEN_INVALID_IDENTIFIER(index, expectedValue) \
    EXPECT_TOKEN_TYPE(index, InvalidIdentifier);              \
    EXPECT_THAT(TO_INVALID_IDENTIFIER(tokenizer.get_token(index))->value, expectedValue)
#define EXPECT_TOKEN_KEYWORD(index, expectedValue) \
    EXPECT_TOKEN_TYPE(index, Keyword);             \
    EXPECT_THAT(TO_KEYWORD(tokenizer.get_token(index))->value, expectedValue)
#define EXPECT_TOKEN_PARENTHESIS(index, expectedValue) \
    EXPECT_TOKEN_TYPE(index, Parenthesis);             \
    EXPECT_THAT(TO_PARENTHESIS(tokenizer.get_token(index))->value, expectedValue)
#define EXPECT_TOKEN_SEPARATOR(index, expectedValue) \
    EXPECT_TOKEN_TYPE(index, Separator);             \
    EXPECT_THAT(TO_SEPARATOR(tokenizer.get_token(index))->value, expectedValue)
#define EXPECT_TOKEN_OPERATOR(index, expectedValue) \
    EXPECT_TOKEN_TYPE(index, Operator);             \
    EXPECT_THAT(TO_OPERATOR(tokenizer.get_token(index))->value, expectedValue)

#define EXPECT_TOKEN_UNKNOWN(index, expectedValue) \
    EXPECT_TOKEN_TYPE(index, Unknown);             \
    EXPECT_THAT(TO_UNKNOWN(tokenizer.get_token(index))->value, expectedValue)

TEST(Tokenizer, Extract_Number)
{
    DEFINE_TOKEN("54");
    EXPECT_TOKEN_COUNT(1);
    EXPECT_TOKEN_INTEGER(0, 54);
}

TEST(Tokenizer, Extract_Float)
{
    DEFINE_TOKEN("54.5");
    EXPECT_TOKEN_COUNT(1);
    EXPECT_TOKEN_FLOAT(0, 54.5);
}

TEST(Tokenizer, Extract_Negative_Number)
{
    DEFINE_TOKEN("-54");
    EXPECT_TOKEN_COUNT(1);
    EXPECT_TOKEN_INTEGER(0, -54);
}

TEST(Tokenizer, Extract_Negative_Float)
{
    DEFINE_TOKEN("-54.5");
    EXPECT_TOKEN_COUNT(1);
    EXPECT_TOKEN_FLOAT(0, -54.5);
}

TEST(Tokenizer, Extract_Float_Without_Fraction)
{
    DEFINE_TOKEN(".54f");
    EXPECT_TOKEN_COUNT(1);
    EXPECT_TOKEN_FLOAT(0, 0.54);
}

TEST(Tokenizer, Extract_Float_Without_Fraction_And_Negative)
{
    DEFINE_TOKEN("-.54f");
    EXPECT_TOKEN_COUNT(1);
    EXPECT_TOKEN_FLOAT(0, -0.54);
}

TEST(Tokenizer, Extract_Float_Without_Fraction_And_Negative_And_Without_f)
{
    DEFINE_TOKEN("54f");
    EXPECT_TOKEN_COUNT(1);
    EXPECT_TOKEN_FLOAT(0, 54);
}

TEST(Tokenizer, Extract_Float_Without_Fraction_And_Negative_And_Without_f_And_Without_Dot)
{
    DEFINE_TOKEN("-54f");
    EXPECT_TOKEN_COUNT(1);
    EXPECT_TOKEN_FLOAT(0, -54);
}

TEST(Tokenizer, Extract_NormalString)
{
    DEFINE_TOKEN(R"("Hello World")");
    EXPECT_TOKEN_COUNT(1);
    EXPECT_TOKEN_STRING(0, "Hello World");
}

TEST(Tokenizer, Extract_String_With_Escape_Character)
{
    DEFINE_TOKEN(R"("Hello\nWorld")");
    EXPECT_TOKEN_COUNT(1);
    EXPECT_TOKEN_STRING(0, "Hello\\nWorld");
}

TEST(Tokenizer, Extract_String_With_Escape_Character_And_Double_Quotes)
{
    DEFINE_TOKEN(R"("Hello\"World")");
    EXPECT_TOKEN_COUNT(1);
    EXPECT_TOKEN_STRING(0, "Hello\\\"World");
}

TEST(Tokenizer, String_with_single_quote)
{
    DEFINE_TOKEN(R"('Hello World')");
    EXPECT_TOKEN_COUNT(1);
    EXPECT_TOKEN_STRING(0, "Hello World");
}

TEST(Tokenizer, String_with_single_quote_and_escape_character)
{
    DEFINE_TOKEN(R"('Hello\nWorld')");
    EXPECT_TOKEN_COUNT(1);
    EXPECT_TOKEN_STRING(0, "Hello\\nWorld");
}

TEST(Tokenizer, string_with_single_quote_and_double_quote_insde)
{
    DEFINE_TOKEN(R"('Hello\"World')");
    EXPECT_TOKEN_COUNT(1);
    EXPECT_TOKEN_STRING(0, "Hello\\\"World");
}

TEST(Tokenizer, extract_multiple_tokens)
{
    DEFINE_TOKEN("54.5 'Hello World' 54");
    EXPECT_TOKEN_COUNT(3);
    EXPECT_TOKEN_FLOAT(0, 54.5);
    EXPECT_TOKEN_STRING(1, "Hello World");
    EXPECT_TOKEN_INTEGER(2, 54);
}

TEST(Tokenizer, extract_with_unknown_token)
{
    DEFINE_TOKEN("~325");
    EXPECT_TOKEN_COUNT(2);
    EXPECT_TOKEN_UNKNOWN(0, "~");
    EXPECT_TOKEN_INTEGER(1, 325);
}

TEST(Tokenizer, extract_identifier)
{
    DEFINE_TOKEN("hello_world");
    EXPECT_TOKEN_COUNT(1);
    EXPECT_TOKEN_IDENTIFIER(0, "hello_world");
}

TEST(Tokenizer, extract_start_with_number_end_with_string)
{
    DEFINE_TOKEN("123hello_world");
    EXPECT_TOKEN_COUNT(1);
    EXPECT_TOKEN_INVALID_IDENTIFIER(0, "123hello_world");
}

TEST(Tokenizer, extract_identifier_with_number)
{
    DEFINE_TOKEN("hello123");
    EXPECT_TOKEN_COUNT(1);
    EXPECT_TOKEN_IDENTIFIER(0, "hello123");
}

TEST(Tokenizer, extract_keyword)
{
    DEFINE_TOKEN("if");
    EXPECT_TOKEN_COUNT(1);
    EXPECT_TOKEN_KEYWORD(0, "if");
}

TEST(Tokenizer, extract_similar_identifer_keyword)
{
    DEFINE_TOKEN("if_else else");
    EXPECT_TOKEN_COUNT(2);
    EXPECT_TOKEN_IDENTIFIER(0, "if_else");
    EXPECT_TOKEN_KEYWORD(1, "else");
}

TEST(Tokenizer, extract_parenthesis)
{
    DEFINE_TOKEN("{(123)}[]");
    EXPECT_TOKEN_COUNT(7);
    EXPECT_TOKEN_PARENTHESIS(0, "{");
    EXPECT_TOKEN_PARENTHESIS(1, "(");
    EXPECT_TOKEN_INTEGER(2, 123);
    EXPECT_TOKEN_PARENTHESIS(3, ")");
    EXPECT_TOKEN_PARENTHESIS(4, "}");
    EXPECT_TOKEN_PARENTHESIS(5, "[");
    EXPECT_TOKEN_PARENTHESIS(6, "]");
}

TEST(Tokenizer, extract_if_statement)
{
    DEFINE_TOKEN("if (123) { 54f; } else { 54; }");
    EXPECT_TOKEN_COUNT(13);
    EXPECT_TOKEN_KEYWORD(0, "if");
    EXPECT_TOKEN_PARENTHESIS(1, "(");
    EXPECT_TOKEN_INTEGER(2, 123);
    EXPECT_TOKEN_PARENTHESIS(3, ")");
    EXPECT_TOKEN_PARENTHESIS(4, "{");
    EXPECT_TOKEN_FLOAT(5, 54);
    EXPECT_TOKEN_SEPARATOR(6, ";");
    EXPECT_TOKEN_PARENTHESIS(7, "}");
    EXPECT_TOKEN_KEYWORD(8, "else");
    EXPECT_TOKEN_PARENTHESIS(9, "{");
    EXPECT_TOKEN_INTEGER(10, 54);
    EXPECT_TOKEN_SEPARATOR(11, ";");
    EXPECT_TOKEN_PARENTHESIS(12, "}");
}

TEST(Tokenizer, extract_uppercase_keyword_as_identifier)
{
    DEFINE_TOKEN("IF");
    EXPECT_TOKEN_COUNT(1);
    EXPECT_TOKEN_IDENTIFIER(0, "IF");
}

TEST(Tokenizer, extract_semi_colon)
{
    DEFINE_TOKEN(";");
    EXPECT_TOKEN_COUNT(1);
    EXPECT_TOKEN_SEPARATOR(0, ";");
}

TEST(Tokenizer, extract_define_statement)
{
    DEFINE_TOKEN("let a, b = 3.14;");
    EXPECT_TOKEN_COUNT(7);
    EXPECT_TOKEN_KEYWORD(0, "let");
    EXPECT_TOKEN_IDENTIFIER(1, "a");
    EXPECT_TOKEN_SEPARATOR(2, ",");
    EXPECT_TOKEN_IDENTIFIER(3, "b");
    EXPECT_TOKEN_OPERATOR(4, "=");
    EXPECT_TOKEN_FLOAT(5, 3.14);
    EXPECT_TOKEN_SEPARATOR(6, ";");
}

TEST(Tokenizer, extract_checking_statement)
{
    DEFINE_TOKEN(" i     == 3.14;  \n   i != 3.14f;");
    EXPECT_TOKEN_COUNT(8);
    EXPECT_TOKEN_IDENTIFIER(0, "i");
    EXPECT_TOKEN_OPERATOR(1, "==");
    EXPECT_TOKEN_FLOAT(2, 3.14);
    EXPECT_TOKEN_SEPARATOR(3, ";");
    EXPECT_TOKEN_IDENTIFIER(4, "i");
    EXPECT_TOKEN_OPERATOR(5, "!=");
    EXPECT_TOKEN_FLOAT(6, 3.14);
    EXPECT_TOKEN_SEPARATOR(7, ";");
}