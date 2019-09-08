#include <openssl/aes.h>
#include "openssl/evp.h"

int openssl_aes_cbc_encrypt(char* in, size_t len, char* out);
int openssl_aes_cbc_decrypt(char* in, size_t len, char* out);
int openssl_aes_ecb_enrypt(char* in, size_t len,char* out);
int openssl_aes_ecb_decrypt(char* in,size_t len, char* out);
/**每个接口都将输入数据的长度传递进去，因为交给上一层去获取数据长度，会更准确一些**/