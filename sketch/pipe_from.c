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
    printf("%d\n", fileno(stdin));
    FILE *pipe = popen("/Users/eric/Documents/sketchbook/to", "w");
    char *message = "hello world";
    fwrite(message, 12, 1, pipe);
    pclose(pipe);
    return 0;
}
