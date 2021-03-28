//
//  ExampleStructure.h
//  sketch
//
//  Created by Eric Meehan on 3/27/21.
//

#ifndef ExampleStructure_h
#define ExampleStructure_h

struct ExampleStructure decode_ex(void *data);


struct ExampleStructure
{
    unsigned char i[64];
    unsigned char previous_hash[64];
    unsigned long size;
    unsigned long nonce;
    void *data;
};

#endif /* ExampleStructure_h */
