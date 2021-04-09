//
//  main.c
//  sketch
//
//  Created by Eric Meehan on 3/24/21.
//

#include "../../libeom/libeom.h"
#include <stdio.h>
#include <string.h>

#include "Block.h"
#include "Transaction.h"

struct Block * create_transaction_block()
{
    struct Block *block = malloc(sizeof(struct Block) + sizeof(struct Transaction));
    for (int i = 0; i < 63; i++)
    {
        block->headers.fingerprint[i] = 'a';
        block->headers.previous_hash[i] = 'b';
    }
    block->headers.size = sizeof(struct Block) + sizeof(struct Transaction) - 1;
    block->headers.nonce = 0;
    strcpy(block->headers.timestamp, "2021-04-01 23:10:10");
    
    struct Transaction *transaction = (void *)&block->data;
    for (int i = 0; i < 63; i++)
    {
        transaction->headers.to[i] = 'c';
        transaction->headers.from[i] = 'd';
    }
    transaction->headers.base = 10;
    transaction->headers.nonce = 0;
    transaction->headers.precision = 1;
    transaction->data = 125;
    
    return block;
}

int main(int argc, const char * argv[])
{
    struct Block *block = create_transaction_block();
    printf("%lu\n\n", sizeof(struct BlockHeaders));
    printf("Fingerprint: %s\nPrevious Hash: %s\nSize: %lu\nNonce: %lu\nTimestamp: %s\n\n", block->headers.fingerprint, block->headers.previous_hash, block->headers.size, block->headers.nonce, block->headers.timestamp);
    printf("To: %s\nFrom: %s\nAmount: %d\n", ((struct Transaction *)&block->data)->headers.to, ((struct Transaction *)&block->data)->headers.from, ((struct Transaction *)&block->data)->data);
    return 0;
}
