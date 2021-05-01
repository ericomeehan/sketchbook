#include "my512.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *data = "abc";
    unsigned char digest[64];
    struct sha512 md;
    sha512_init(&md);
    sha512_process(&md, (unsigned char *)data, strlen(data));
    sha512_done(&md, digest);
    for (int i = 0; i < 64; i++)
    {
        printf("%X", digest[i]);
    }
    printf("\n");
}
