//
//  Block.c
//  sketch
//
//  Created by Eric Meehan on 3/29/21.
//

#include "Block.h"
#include <stdlib.h>
#include <string.h>

void * connect_headers_to_data(struct BlockHeders *headers, void *data, unsigned long size)
{
    void *block = calloc(size, 1);
    memcpy(block, headers, sizeof(struct BlockHeders));
    memcpy(block + sizeof(struct BlockHeders), data, size - sizeof(struct BlockHeders));
    return block;
}
