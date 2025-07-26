#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <nttlang/tokenizer.h>

using namespace ntt;

TEST(Tokenizer, Extract_Number)
{
    Tokenizer tokenizer("54");
    tokenizer.extract();
    EXPECT_THAT(tokenizer.get_token(0)->type, TokenType::Integer);
    EXPECT_THAT(TO_NUMBER(tokenizer.get_token(0))->value, 54);
}
