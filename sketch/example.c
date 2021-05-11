//
//  main.c
//  sketch
//
//  Created by Eric Meehan on 3/24/21.
//

// Code originally from https://pagefault.blog/2019/04/22/how-to-sign-and-verify-using-openssl/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/sha.h>
 
// Buffer for file read operations. The buffer must be able to accomodate
// the RSA signature in whole (e.g. 4096-bit RSA key produces 512 byte signature)
#define BUFFER_SIZE 512
static unsigned char buffer[BUFFER_SIZE];

int pem_password_callback(char *buf, int max_len, int flag, void *ctx)
{
    const char* PASSWD = getpass("Password: ");
    int len = strlen(PASSWD);

    if(len > max_len)
        return 0;

    memcpy(buf, PASSWD, len);
    return len;
}


int crypto_init(void);
int crypto_init()
{
  /* Load the human readable error strings for libcrypto */
  ERR_load_crypto_strings();

  /* Load all digest and cipher algorithms */
  OpenSSL_add_all_algorithms();

  /* Load config file, and other important initialisation */
  OPENSSL_config(NULL);

  /* ... Do some crypto stuff here ... */

  /* Clean up */

  /* Removes all digests and ciphers */
  EVP_cleanup();

  /* if you omit the next, a small leak may be left when you make use of the BIO (low level API) for e.g. base64 transformations */
  CRYPTO_cleanup_all_ex_data();

  /* Remove error strings */
  ERR_free_strings();

  return 0;
}


 
int main(int argc, char *argv[])
{
    crypto_init();
    
    if(argc != 4)
    {
        fprintf(stderr, "Usage: %s datafile signature_file public_key\n", argv[0]);
        return -1;
    }
    const char* filename = argv[1];
    const char* sigfile = argv[2];
    const char* pubkeyfile = argv[3];
 
    unsigned bytes = 0;
 
    // Calculate SHA512 digest for datafile
    FILE* datafile = fopen(filename , "rb");
 
    // Buffer to hold the calculated digest
    unsigned char digest[SHA512_DIGEST_LENGTH];
    SHA512_CTX ctx;
    SHA512_Init(&ctx);
 
    // Read data in chunks and feed it to OpenSSL SHA512
    while((bytes = fread(buffer, 1, BUFFER_SIZE, datafile)))
    {
        SHA512_Update(&ctx, buffer, bytes);
    }
 
    SHA512_Final(digest, &ctx);
    fclose(datafile);
 
    // Read signature from file
    FILE* sign = fopen (sigfile , "r");
 
    bytes = fread(buffer, 1, BUFFER_SIZE, sign);
    fclose(sign);
 
    // Verify that calculated digest and signature match
    FILE* pubkey = fopen(pubkeyfile, "r");
 
    // Read public key from file
    RSA* rsa_pubkey = PEM_read_RSA_PUBKEY(pubkey, NULL, pem_password_callback, NULL);
 
    // Decrypt signature (in buffer) and verify it matches
    // with the digest calculated from data file.
    int result = RSA_verify(NID_sha512, digest, SHA512_DIGEST_LENGTH,
                            buffer, bytes, rsa_pubkey);
    RSA_free(rsa_pubkey);
    fclose(pubkey);
 
    if(result == 1)
    {
        printf("Signature is valid\n");
        return 0;
    }
    else
    {
        printf("Signature is invalid\n");
        return 1;
    }
}
