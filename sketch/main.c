//
//  main.c
//  sketch
//
//  Created by Eric Meehan on 3/24/21.
//

#include "../../libeom/libeom.h"

#include <openssl/evp.h>

#include <stdio.h>
#include <stdlib.h>

#include <math.h>

void write_image_into_eson()
{
    // Originally main, was used to create example_eson.block
    FILE *eson = fopen("/Users/eric/Documents/sketchbook/example.eson", "ab");
    FILE *eric_original = fopen("/Users/eric/Documents/sketchbook/eric_original.jpg", "rb");
    
    // Get the size of the original
    fseek(eric_original, 0, SEEK_END);
    long file_size = ftell(eric_original);
    fseek(eric_original, 0, SEEK_SET);
        
    void *file_data = malloc(file_size + 1);
    fread(file_data, file_size, file_size, eric_original);
    fclose(eric_original);
    ((char *)file_data)[file_size] = '}';
    
    fwrite(file_data, file_size, file_size, eson);
    
    fclose(eson);
}

int main()
{
    //write_image_into_eson();
    // Now read the contents from eson and write them to a new image file
    FILE *eson = fopen("/Users/eric/Documents/sketchbook/example.eson", "r");
    fseek(eson, 0, SEEK_END);
    long eson_size = ftell(eson);
    fseek(eson, 0, SEEK_SET);
    
    double difficulty = 10 * sqrt(log10(eson_size)) + 1;
    
    printf("%ld\n%f\n", eson_size, difficulty);
    
    void *data = malloc(eson_size);
    fread(data, eson_size, eson_size, eson);
    
    // 274 characters before file
    
    long output_size = eson_size - 275;
    void *output = malloc(output_size);
    for (int i = 275; i < eson_size - 1; i++)
    {
        ((char *)output)[i - 275] = ((char *)data)[i];
    }
    
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, EVP_sha512(), NULL);
    EVP_DigestUpdate(mdctx, output, output_size);
    unsigned char result[64] = {0};
    unsigned int x = 64;
    EVP_DigestFinal_ex(mdctx, result, &x);
    
    for (int i = 0; i < 64; i++)
    {
        printf("%02X", result[i]);
    }
    
    FILE *output_file = fopen("/Users/eric/Desktop/output.jpg", "w");
    fwrite(output, output_size, output_size, output_file);
    fclose(output_file);
    return 0;
}

int main_t()
{
    FILE *output = fopen("/Users/eric/Desktop/output.txt", "r");
    fseek(output, 0, SEEK_END);
    long fsize = ftell(output);
    fseek(output, 0, SEEK_SET);
    
    void *data = malloc(fsize);
    fread(data, fsize, fsize, output);
    
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, EVP_sha512(), NULL);
    EVP_DigestUpdate(mdctx, data, fsize);
    unsigned char result[64] = {0};
    unsigned int x = 64;
    EVP_DigestFinal_ex(mdctx, result, &x);
    
    for (int i = 0; i < 64; i++)
    {
        printf("%02X", result[i]);
    }
    return 0;
}
