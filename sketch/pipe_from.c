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
    int fd = open("pipe", O_RDWR);
    
    char *message = "hello world";
    write(fd, message, strlen(message) + 1);
    
    FILE *process = popen("./to", "w");
    pclose(process);
    
    char buffer[256];
    read(fd, buffer, 256);
    
    printf("%s\n", buffer);
    
    close(fd);
    
    return 0;
}
