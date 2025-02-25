#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <stdlib.h>
#include <string.h>

/**
 * Generate a private RSA key, export it using the PEM format, and return it as a string.
 *
 * @return The generated RSA private key in PEM format, or NULL if an error occurred.
 */
char *create_private_key() {
    const int key_length = 2048; // Recommended RSA key length
    RSA *rsa = RSA_generate_key(key_length, RSA_F4, NULL, NULL);
    if (rsa == NULL) {
        fprintf(stderr, "Error generating RSA key: %s\n", ERR_error_string(ERR_get_error(), NULL));
        return NULL;
    }

    BIO *bio = BIO_new(BIO_s_mem());
    if (bio == NULL) {
        RSA_free(rsa);
        fprintf(stderr, "Error creating BIO: %s\n", ERR_error_string(ERR_get_error(), NULL));
        return NULL;
    }

    if (PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL) != 1) {
        BIO_free(bio);
        RSA_free(rsa);
        fprintf(stderr, "Error writing RSA key to BIO: %s\n", ERR_error_string(ERR_get_error(), NULL));
        return NULL;
    }

    BUF_MEM *buf;
    BIO_get_mem_ptr(bio, &buf);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free(bio);
    RSA_free(rsa);

    char *private_key = (char *)malloc(buf->length + 1);
    if (private_key == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return NULL;
    }

    memcpy(private_key, buf->data, buf->length);
    private_key[buf->length] = '\0'; // Null-terminate the string

    return private_key;
}