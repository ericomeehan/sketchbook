//
//  main.c
//  sketch
//
//  Created by Eric Meehan on 3/24/21.
//

#include "../../libeom/libeom.h"
#include <stdio.h>

enum
{
    a,
};

// argv[0] = program name
// argv[1] = first arg

int main(int argc, const char * argv[]) {
    for (int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }
}
