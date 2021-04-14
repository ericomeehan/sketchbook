#ifndef SHA256_BLOCK_SHA256_H
#define SHA256_BLOCK_SHA256_H

#include <stdlib.h>

#define blk_SHA256_BLKSIZE 64

static inline uint32_t get_be32(const void *ptr)
{
    const unsigned char *p = ptr;
    return    (uint32_t)p[0] << 24 |
        (uint32_t)p[1] << 16 |
        (uint32_t)p[2] <<  8 |
        (uint32_t)p[3] <<  0;
}

static inline void put_be32(void *ptr, uint32_t value)
{
    unsigned char *p = ptr;
    p[0] = value >> 24;
    p[1] = value >> 16;
    p[2] = value >>  8;
    p[3] = value >>  0;
}

struct blk_SHA256_CTX {
	uint32_t state[8];
	uint64_t size;
	uint32_t offset;
	uint8_t buf[blk_SHA256_BLKSIZE];
};

typedef struct blk_SHA256_CTX blk_SHA256_CTX;

void blk_SHA256_Init(blk_SHA256_CTX *ctx);
void blk_SHA256_Update(blk_SHA256_CTX *ctx, const void *data, size_t len);
void blk_SHA256_Final(unsigned char *digest, blk_SHA256_CTX *ctx);

#define platform_SHA256_CTX blk_SHA256_CTX
#define platform_SHA256_Init blk_SHA256_Init
#define platform_SHA256_Update blk_SHA256_Update
#define platform_SHA256_Final blk_SHA256_Final

#endif
