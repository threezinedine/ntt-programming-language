#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <nttlang/tokenizer.h>

using namespace ntt;

#define DEFINE_TOKEN(content)     \
    Tokenizer tokenizer(content); \
    tokenizer.extract()

TEST(Tokenizer, Extract_Number)
{
    DEFINE_TOKEN("54");
    EXPECT_THAT(tokenizer.get_token(0)->type, TokenType::Integer);
    EXPECT_THAT(TO_INTEGER(tokenizer.get_token(0))->value, 54);
}

TEST(Tokenizer, Extract_Float)
{
    DEFINE_TOKEN("54.5");
    EXPECT_THAT(tokenizer.get_token(0)->type, TokenType::Float);
    EXPECT_THAT(TO_FLOAT(tokenizer.get_token(0))->value, 54.5);
}

TEST(Tokenizer, Extract_Negative_Number)
{
    DEFINE_TOKEN("-54");
    EXPECT_THAT(tokenizer.get_token(0)->type, TokenType::Integer);
    EXPECT_THAT(TO_INTEGER(tokenizer.get_token(0))->value, -54);
}

TEST(Tokenizer, Extract_Negative_Float)
{
    DEFINE_TOKEN("-54.5");
    EXPECT_THAT(tokenizer.get_token(0)->type, TokenType::Float);
    EXPECT_THAT(TO_FLOAT(tokenizer.get_token(0))->value, -54.5);
}

TEST(Tokenizer, Extract_Float_Without_Fraction)
{
    DEFINE_TOKEN(".54f");
    EXPECT_THAT(tokenizer.get_token(0)->type, TokenType::Float);
    EXPECT_THAT(TO_FLOAT(tokenizer.get_token(0))->value, 0.54);
}

TEST(Tokenizer, Extract_Float_Without_Fraction_And_Negative)
{
    DEFINE_TOKEN("-.54f");
    EXPECT_THAT(tokenizer.get_token(0)->type, TokenType::Float);
    EXPECT_THAT(TO_FLOAT(tokenizer.get_token(0))->value, -0.54);
}

TEST(Tokenizer, Extract_Float_Without_Fraction_And_Negative_And_Without_f)
{
    DEFINE_TOKEN("54f");
    EXPECT_THAT(tokenizer.get_token(0)->type, TokenType::Float);
    EXPECT_THAT(TO_FLOAT(tokenizer.get_token(0))->value, 54);
}

TEST(Tokenizer, Extract_Float_Without_Fraction_And_Negative_And_Without_f_And_Without_Dot)
{
    DEFINE_TOKEN("-54f");
    EXPECT_THAT(tokenizer.get_token(0)->type, TokenType::Float);
    EXPECT_THAT(TO_FLOAT(tokenizer.get_token(0))->value, -54);
}

TEST(Tokenizer, Extract_NormalString)
{
    DEFINE_TOKEN(R"("Hello World")");
    EXPECT_THAT(tokenizer.get_token(0)->type, TokenType::String);
    EXPECT_THAT(TO_STRING(tokenizer.get_token(0))->value, "Hello World");
}

TEST(Tokenizer, Extract_String_With_Escape_Character)
{
    DEFINE_TOKEN(R"("Hello\nWorld")");
    EXPECT_THAT(tokenizer.get_token(0)->type, TokenType::String);
    EXPECT_THAT(TO_STRING(tokenizer.get_token(0))->value, "Hello\\nWorld");
}

TEST(Tokenizer, Extract_String_With_Escape_Character_And_Double_Quotes)
{
    DEFINE_TOKEN(R"("Hello\"World")");
    EXPECT_THAT(tokenizer.get_token(0)->type, TokenType::String);
    EXPECT_THAT(TO_STRING(tokenizer.get_token(0))->value, "Hello\\\"World");
}

TEST(Tokenizer, String_with_single_quote)
{
    DEFINE_TOKEN(R"('Hello World')");
    EXPECT_THAT(tokenizer.get_token(0)->type, TokenType::String);
    EXPECT_THAT(TO_STRING(tokenizer.get_token(0))->value, "Hello World");
}

TEST(Tokenizer, String_with_single_quote_and_escape_character)
{
    DEFINE_TOKEN(R"('Hello\nWorld')");
    EXPECT_THAT(tokenizer.get_token(0)->type, TokenType::String);
    EXPECT_THAT(TO_STRING(tokenizer.get_token(0))->value, "Hello\\nWorld");
}

TEST(Tokenizer, string_with_single_quote_and_double_quote_insde)
{
    DEFINE_TOKEN(R"('Hello\"World')");
    EXPECT_THAT(tokenizer.get_token(0)->type, TokenType::String);
    EXPECT_THAT(TO_STRING(tokenizer.get_token(0))->value, "Hello\\\"World");
}