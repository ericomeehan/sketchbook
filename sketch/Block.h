//
//  Block.h
//  sketch
//
//  Created by Eric Meehan on 3/29/21.
//

#ifndef Block_h
#define Block_h

#include <stdio.h>

struct BlockHeders
{
    unsigned char id[64];
    unsigned char previous_hash[64];
    unsigned long nonce;
    unsigned long size;
    char data[];
};

#endif /* Block_h */
