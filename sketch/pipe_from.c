//
//  main.c
//  sketch
//
//  Created by Eric Meehan on 3/24/21.
//

#include "../../libeom/libeom.h"
#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[])
{
    char message[256];
    do
    {
        memset(message, 0, 256);
        fread(message, 256, 1, stdin);
        FILE *pipe = popen("/Users/eric/Documents/sketchbook/to", "w");
        fwrite(message, 256, 1, pipe);
        pclose(pipe);
    } while (strcmp(message, "quit\n") != 0);
}
