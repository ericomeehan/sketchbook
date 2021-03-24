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
    
    void *data = malloc(fsize + 1);
    fread(data, fsize, fsize, image);
    ((char *)data)[fsize] = '}';
    fclose(image);
    
    fwrite(data, fsize + 1, fsize + 1, example_eson);
    fclose(example_eson);
}
