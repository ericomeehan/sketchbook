//
//  main.c
//  sketch
//
//  Created by Eric Meehan on 3/24/21.
//

#include "../../libeom/libeom.h"

#include <openssl/evp.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

struct Block
{
    long nonce;
    double timestamp;
};

int main(int argc, const char * argv[]) {
    
    FILE *output = fopen("output.csv", "w");
    char *headers = "bytes,difficulty,nonce,time\n";
    fwrite(headers, strlen(headers), strlen(headers), output);
    
    for (int i = 0; i < 36; i++)
    {
        struct Block block;
        block.timestamp = clock();
        block.nonce = 0;
        int size = 0;
        EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
        EVP_DigestInit_ex(mdctx, EVP_sha512(), NULL);
        do
        {
            EVP_DigestUpdate(mdctx, &block, sizeof(block));
            block.nonce += 1;
            size = EVP_MD_CTX_block_size(mdctx);
            unsigned char result[64] = {0};
            unsigned int x = 64;
            EVP_DigestFinal_ex(mdctx, result, &x);
            for (int i = 0; i < 64; i++)
            {
                printf("%02X", result[i]);
            }
            printf("\n\n%d\n\n", size);
            
        }
        while (size > 127);
        unsigned char result[64] = {0};
        unsigned int x = 64;
        EVP_DigestFinal_ex(mdctx, result, &x);
        for (int i = 0; i < 64; i++)
        {
            printf("%02X", result[i]);
        }
    
        printf("\n\n");
        
    }
}
