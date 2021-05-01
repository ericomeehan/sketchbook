//
//  my512.h
//  sketch
//
//  Created by Eric Meehan on 4/26/21.
//

#ifndef my512_h
#define my512_h

#include <stdlib.h>

struct sha512
{
    unsigned long length;
    unsigned long state[8];
    unsigned long curlen;
    unsigned char buf[128];
};

void sha512_init(struct sha512 *md);
void sha512_process(struct sha512 *md, const void *in, unsigned long inlen);
void sha512_done(struct sha512 *md, unsigned char *out);

#endif /* my512_h */
