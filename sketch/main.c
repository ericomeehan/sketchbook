//
//  main.c
//  sketch
//
//  Created by Eric Meehan on 3/24/21.
//

#include "../../libeom/libeom.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, const char * argv[]) {
    FILE *a = fopen("/Users/eric/Desktop/image.jpg", "r");
    long size = get_file_size(a);
    
    char *header = "{data:";
    void *image = malloc(size + strlen(header));
    memcpy(image, header, strlen(header));
    fread(image + strlen(header), size, size, a);
    fclose(a);
    
    FILE *b = fopen("/Users/eric/Desktop/copy.jpg", "w");
    fwrite(image, size, size, b);
    fclose(b);
    
    b = fopen("/Users/eric/Desktop/copy.jpg", "r");
    FILE *c = fopen("/Users/eric/Desktop/second_copy.jpg", "w");
    long b_size = get_file_size(b);
    
    void *second_copy = malloc(b_size);
    fread(second_copy, b_size, b_size, b);
    fclose(b);
    
    void *final_image = malloc(b_size - 6);
    memcpy(final_image, second_copy + 6, b_size - 6);
    fwrite(final_image, b_size - 6, b_size - 6, c);
    fclose(c);
    
}
