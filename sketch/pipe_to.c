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
    int fd = open("pipe", O_RDWR);
    read(fd, buffer, 256);
    write(fd, buffer, strlen(buffer) + 1);
    close(fd);
}
