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
    const char *cmd;
    
    cmd = argv[0];
    if (!cmd)
    {
        cmd = "help";
    }
}
