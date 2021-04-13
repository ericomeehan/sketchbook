//
//  pipe_to.c
//  sketchbook
//
//  Created by Eric Meehan on 4/10/21.
//

#include "../../libeom/libeom.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
    void *data = alloca(256);
    memset(data, 0, 256);
    fread(data, 256, 1, stdin);
    
    if (isatty(fileno(stdin)))
    {
        printf("Terminal\n");
    }
    else
    {
        printf("Pipe\n");
    }
    printf("%s\n", data);
    
    return 0;
}
