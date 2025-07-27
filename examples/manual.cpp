#include <cstdio>
#include <nttlang/nttlang.h>

using namespace ntt;

int main(void)
{
    Tokenizer tokenizer("\"Hello\\\"World\"");
    tokenizer.extract();
    ASSERT_TOKEN_AS_INTEGER(tokenizer.get_token(0));
    printf("Token value: %s\n", TO_STRING(tokenizer.get_token(0))->value.c_str());
    return 0;
}