#include "sha256.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long get_file_size_internal(FILE *file)
{
    fseek(file, 0, SEEK_END);
    unsigned long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

int main()
{
    unsigned char digest[32];
    FILE *f = fopen("/Users/eric/Desktop/hashable", "r");
    unsigned long size = get_file_size_internal(f);
    void *data = malloc(size);
    memset(data, 0, size);
    
    fread(data, 0, size, f);
    fclose(f);
    
    blk_SHA256_CTX ctx;
    blk_SHA256_Init(&ctx);
    blk_SHA256_Update(&ctx, data, 1);
    blk_SHA256_Final(digest, &ctx);
    for (int i = 0; i < 32; i++)
    {
        printf("%02X", digest[i]);
    }
    printf("\n");
    return 0;
}
