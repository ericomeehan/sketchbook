//
//  Block.h
//  sketch
//
//  Created by Eric Meehan on 4/1/21.
//

#ifndef Block_h
#define Block_h

struct BlockHeaders
{
    unsigned char previous_hash[64];
    unsigned long nonce;
    unsigned char fingerprint[64];
    unsigned char timestamp[20];
    unsigned long size;
} __attribute__((packed));

struct Block
{
    struct BlockHeaders headers;
    unsigned char data;
} __attribute__((packed));

#endif /* Block_h */
