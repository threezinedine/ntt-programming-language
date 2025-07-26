#include <cstdio>
#include <nttlang/nttlang.h>

using namespace ntt;

int main(void)
{
    Tokenizer tokenizer("54");
    tokenizer.extract();
    printf("Token value: %d\n", TO_NUMBER(tokenizer.get_token(0))->value);
    return 0;
}