//
//  main.c
//  sketch
//
//  Created by Eric Meehan on 3/24/21.
//

#include "../../libeom/libeom.h"

#include <openssl/evp.h>
#include <openssl/bn.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

struct Block
{
    long nonce;
    double timestamp;
};

int main(int argc, const char * argv[]) {
    
    FILE *output = fopen("output.csv", "w");
    char *headers = "bytes,difficulty,nonce,time\n";
    fwrite(headers, strlen(headers), strlen(headers), output);
    
    
    srand(clock());
    
    for (long i = 1; i < 1000000000000; i++)
    {
        
        long bytes = rand() % 10000000001;
        
        
        struct Block block;
        block.timestamp = clock();
        block.nonce = 0;
        int size = 0;
        EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
        EVP_DigestInit_ex(mdctx, EVP_sha512(), NULL);
        
        
        BN_CTX *ctx = BN_CTX_new();
        
        char base[] = "2";
        BIGNUM *a = BN_new();
        BN_dec2bn(&a, base);
        
        double difficulty = 10 * sqrt(log10(bytes));
        printf("%f difficulty...\n", difficulty);
        
        char *exponent = malloc(5);
        sprintf(exponent, "%f", 512-difficulty);
        BIGNUM *p = BN_new();
        BN_dec2bn(&p, exponent);
        
        BIGNUM *r = BN_new();
        BN_exp(r, a, p, ctx);
        
        BIGNUM *h = BN_new();
                
        do
        {
            EVP_DigestUpdate(mdctx, &block, sizeof(block));
            block.nonce += 1;
            size = EVP_MD_CTX_block_size(mdctx);
            unsigned char result[64] = {0};
            unsigned int x = 64;
            EVP_DigestFinal_ex(mdctx, result, &x);
            BN_bin2bn(result, 64, h);
        }
        while (BN_cmp(r, h) <= 0);
        
        double end = clock();
        
        printf("\n\n========================\n\n");
        
        unsigned char hash[64] = {0};
        BN_bn2bin(h, hash);
        for (int i = 0; i < 64; i++)
        {
            printf("%02X", hash[64-i]);
        }
        printf("\n\n");
        
        printf("bytes: %ld\n", bytes);
        printf("difficulty: %f\n", difficulty);
        printf("nonce: %ld\n", block.nonce - 1);
        printf("time: %f\n", (end - block.timestamp)/CLOCKS_PER_SEC);
        
        char *result = malloc(255);
        sprintf(result, "%ld,%f,%ld,%f\n", bytes, difficulty, block.nonce - 1, (end - block.timestamp)/CLOCKS_PER_SEC);
        fwrite(result, strlen(result), strlen(result), output);
        
        free(result);
        free(exponent);
    }
    fclose(output);
}
