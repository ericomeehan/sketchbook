//
//  pipe_to.c
//  sketchbook
//
//  Created by Eric Meehan on 4/10/21.
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, const char *argv[])
{
    char buffer[256];
    int pipe = open("pipe", O_RDWR);
    read(pipe, buffer, 256);
    
    printf("%s\n", buffer);
    
    char *reply = "hello yourself";
    write(pipe, reply, strlen(reply) + 1);
    close(pipe);
    return 0;
}
