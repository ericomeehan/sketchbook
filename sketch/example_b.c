// https://stackoverflow.com/questions/12647220/reading-and-writing-rsa-keys-to-a-pem-file-in-c

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

const char* pcszPassphrase = "";

static void gen_callback(int iWhat, int inPrime, void* pParam);
static void init_openssl(void);
static void cleanup_openssl(void);
static int passwd_callback(char *pcszBuff,int size,int rwflag, void *pPass);
static void handle_openssl_error(void);

int main(int argc, char **argv)
{
    int iRet = EXIT_SUCCESS;
    EVP_PKEY* pPrivKey = NULL;
    EVP_PKEY* pPubKey  = NULL;
    FILE*     pFile    = NULL;
    
    init_openssl();

    if((pFile = fopen("~/Documents/keys/eric.pem","rt")) &&
       (pPrivKey = PEM_read_PrivateKey(pFile,NULL,passwd_callback,NULL)))
    {
        fprintf(stderr,"Private key read.\n");
    }
    else
    {
        fprintf(stderr,"Cannot read \"privkey.pem\".\n");
        handle_openssl_error();
        iRet = EXIT_FAILURE;
    }
    if(pFile)
    {
        fclose(pFile);
        pFile = NULL;
    }

    if((pFile = fopen("~/Documents/keys/public.pem","rt")) &&
       (pPubKey = PEM_read_PUBKEY(pFile,&pPubKey,passwd_callback,(void*)pcszPassphrase)))
    {
        fprintf(stderr,"Public key read.\n");
    }
    else
    {
        fprintf(stderr,"Cannot read \"pubkey.pem\".\n");
        handle_openssl_error();
        iRet = EXIT_FAILURE;
    }
    if(pPrivKey)
    {
        EVP_PKEY_free(pPrivKey);
        pPrivKey = NULL;
    }
    if(pPubKey)
    {
        EVP_PKEY_free(pPubKey);
        pPubKey = NULL;
    }
    cleanup_openssl();
    return iRet;
}



void gen_callback(int iWhat, int inPrime, void* pParam)
{
    char c='*';
    switch(iWhat)
    {
        case 0: c = '.';  break;
        case 1: c = '+';  break;
        case 2: c = '*';  break;
        case 3: c = '\n'; break;
    }
    fprintf(stderr,"%c",c);
}

int passwd_callback(char *pcszBuff,int size,int rwflag, void *pPass)
{
    size_t unPass = strlen((char*)pPass);
    if(unPass > (size_t)size)
        unPass = (size_t)size;
    memcpy(pcszBuff, pPass, unPass);
    return (int)unPass;
}

void init_openssl(void)
{
    OpenSSL_add_all_algorithms();
}

void cleanup_openssl(void)
{
    CRYPTO_cleanup_all_ex_data();
    ERR_free_strings();
//    ERR_remove_thread_state(0);
    EVP_cleanup();
}

void handle_openssl_error(void)
{
    ERR_print_errors_fp(stderr);
}
