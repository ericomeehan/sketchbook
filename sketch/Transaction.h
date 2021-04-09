//
//  Transaction.h
//  sketch
//
//  Created by Eric Meehan on 4/1/21.
//

#ifndef Transaction_h
#define Transaction_h

#include "../../libeom/Cryptography.h"

struct TransactionHeaders
{
    unsigned char to[64];
    unsigned char from[64];
    unsigned long nonce;
    unsigned long base;
    unsigned long precision;
} __attribute__((packed));

struct Transaction
{
    struct TransactionHeaders headers;
    unsigned char data;
} __attribute__((packed));



#endif /* Transaction_h */
