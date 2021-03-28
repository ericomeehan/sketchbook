//
//  ExampleStructure.c
//  sketch
//
//  Created by Eric Meehan on 3/27/21.
//

#include "ExampleStructure.h"
#include <string.h>
#include <stdlib.h>

struct ExampleStructure decode_ex(void *data)
{
    struct ExampleStructure *ex = data;
    void *content = malloc(ex->size);
    memcpy(content, ex->data, ex->size);
    ex->data = content;
    return *ex;
}

void * encode_ex(struct ExampleStructure *ex)
{
    void *data = malloc(sizeof(ex) - sizeof(void *) + ex->size);
    memcpy(data, ex, sizeof(ex) - sizeof(void *));
    memcpy(data + sizeof(ex) - sizeof(void *), ex->data, ex->size);
    return data;
}
