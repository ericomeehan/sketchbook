//
//  main.c
//  eson_demo
//
//  Created by Eric Meehan on 3/24/21.
//

#include "../../libeom/libeom.h"

#include <stdio.h>
#include <stdlib.h>

void write_image_into_eson()
{
    // Originally main, was used to create example_eson.block
    FILE *example_eson = fopen("/Users/eric/Documents/sketchbook/example_eson.block", "ab");
    FILE *image = fopen("/Users/eric/Documents/sketchbook/eric_original.jpg", "rb");
    
    // Get the size of the original
    fseek(image, 0, SEEK_END);
    long fsize = ftell(image);
    fseek(image, 0, SEEK_SET);
    
    void *data = malloc(fsize);
    fread(data, fsize, fsize, image);
    fclose(image);
    //((char *)data)[fsize] = '}';
    
    fwrite(data, fsize, fsize, example_eson);
    
    fclose(example_eson);
}


int main()
{
    //write_image_into_eson();
    // Now read the contents from eson and write them to a new image file
    FILE *eson = fopen("/Users/eric/Documents/sketchbook/example_eson.block", "r");
    fseek(eson, 0, SEEK_END);
    long fsize = ftell(eson);
    fseek(eson, 0, SEEK_SET);
    
    void *data = malloc(fsize);
    fread(data, fsize, fsize, eson);
    
    // 274 characters before file
    
    void *image = malloc(fsize - 274);
    for (int i = 274; i < fsize-1; i++)
    {
        ((char *)image)[i - 274] = ((char *)data)[i];
    }
    
    FILE *output = fopen("/Users/eric/Desktop/output.jpg", "w");
    fwrite(image, fsize-274, fsize-274, output);
    fclose(output);
    
}
