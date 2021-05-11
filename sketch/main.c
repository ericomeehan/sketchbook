//
//  main.c
//  sketch
//
//  Created by Eric Meehan on 5/2/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/rsa.h>
#include <openssl/pem.h>

int pem_password_callback(char *buf, int max_len, int flag, void *ctx)
{
    const char* PASSWD = "22046e-02120O-4489m";
    int len = (int)strlen(PASSWD);

    if(len > max_len)
        return 0;

    memcpy(buf, PASSWD, len);
    return len;
}

int main()
{
    printf("1\n");
    FILE *f = fopen("~/Documents/keys/eric_public.pem", "r");
    printf("2\n");
    EVP_PKEY *public;
    printf("3\n");
    
    PEM_read_PUBKEY(f, &public, pem_password_callback, NULL);
    printf("4\n");
    fclose(f);
}
