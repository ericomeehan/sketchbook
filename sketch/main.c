//
//  main.c
//  sketch
//
//  Created by Eric Meehan on 3/24/21.
//

#include "../../libeom/libeom.h"

#include <stdio.h>
#include <stdlib.h>

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
    long fsize = ftell(eson);
    fseek(eson, 0, SEEK_SET);
    
    void *data = malloc(fsize);
    fread(data, fsize, fsize, eson);
    
    // 274 characters before file
    
    void *image = malloc(fsize - 275);
    for (int i = 275; i < fsize-1; i++)
    {
        ((char *)image)[i - 275] = ((char *)data)[i];
    }
    
    FILE *output = fopen("/Users/eric/Desktop/output.jpg", "w");
    fwrite(image, fsize-275, fsize-275, output);
    fclose(output);
    
}
