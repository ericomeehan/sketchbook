//
//  main.c
//  sketch
//
//  Created by Eric Meehan on 3/24/21.
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int pipe = open("pipe", O_RDWR);
    char *hello = "hello world";
    write(pipe, hello, strlen(hello) + 1);
    
    FILE *process = popen("./to", "w");
    pclose(process);
    
    char buffer[256];
    read(pipe, buffer, 256);
    printf("%s\n", buffer);
    
    close(pipe);
    return 0;
}
