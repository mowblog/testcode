#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include "openssl/aes.h"
#include "openssl/evp.h"
#include "openssl/bio.h"
#include "openssl/evp.h"
 #include <openssl/sha.h>
 #include <openssl/hmac.h>
 #include <openssl/bio.h>
 #include <openssl/buffer.h>

//BIO_METHOD * BIO_f_base64(void);

char *base64_encode(const void *b64_encode_this, int encode_this_many_bytes)
{
    BIO *b64_bio, *mem_bio;      //Declares two OpenSSL BIOs: a base64 filter and a memory BIO.
    BUF_MEM *mem_bio_mem_ptr;    //Pointer to a "memory BIO" structure holding our base64 data.
    b64_bio = BIO_new(BIO_f_base64());                      //Initialize our base64 filter BIO.
    mem_bio = BIO_new(BIO_s_mem());                           //Initialize our memory sink BIO.
    BIO_push(b64_bio, mem_bio);            //Link the BIOs by creating a filter-sink BIO chain.
    BIO_set_flags(b64_bio, BIO_FLAGS_BASE64_NO_NL);  //No newlines every 64 characters or less.
    BIO_write(b64_bio, b64_encode_this, encode_this_many_bytes); //Records base64 encoded data.
    BIO_flush(b64_bio);   //Flush data.  Necessary for b64 encoding, because of pad characters.
    BIO_get_mem_ptr(mem_bio, &mem_bio_mem_ptr);  //Store address of mem_bio's memory structure.
    BIO_set_close(mem_bio, BIO_NOCLOSE);   //Permit access to mem_ptr after BIOs are destroyed.
    BIO_free_all(b64_bio);  //Destroys all BIOs in chain, starting with b64 (i.e. the 1st one).
    BUF_MEM_grow(mem_bio_mem_ptr, (*mem_bio_mem_ptr).length + 1);   //Makes space for end null.
    (*mem_bio_mem_ptr).data[(*mem_bio_mem_ptr).length] = '\0';  //Adds null-terminator to tail.
    return (*mem_bio_mem_ptr).data; //Returns base-64 encoded data. (See: "buf_mem_st" struct).
}
char *base64_decode(const void  *b64_decode_this, int decode_this_many_bytes)
{
    BIO *b64_bio, *mem_bio;      //Declares two OpenSSL BIOs: a base64 filter and a memory BIO.
    char *base64_decoded = (char*)calloc( (decode_this_many_bytes*3)/4+1, sizeof(char) ); //+1 = null.
    b64_bio = BIO_new(BIO_f_base64());                      //Initialize our base64 filter BIO.
    mem_bio = BIO_new(BIO_s_mem());                         //Initialize our memory source BIO.
    BIO_write(mem_bio, b64_decode_this, decode_this_many_bytes); //Base64 data saved in source.
    BIO_push(b64_bio, mem_bio);          //Link the BIOs by creating a filter-source BIO chain.
    BIO_set_flags(b64_bio, BIO_FLAGS_BASE64_NO_NL);          //Don't require trailing newlines.
    int decoded_byte_index = 0;   //Index where the next base64_decoded byte should be written.
    while ( 0 < BIO_read(b64_bio, base64_decoded+decoded_byte_index, 1) ){ //Read byte-by-byte.
        decoded_byte_index++; //Increment the index until read of BIO decoded data is complete.
    } //Once we're done reading decoded data, BIO_read returns -1 even though there's no error.
    BIO_free_all(b64_bio);  //Destroys all BIOs in chain, starting with b64 (i.e. the 1st one).
    return base64_decoded;        //Returns base-64 decoded data with trailing null terminator.
}


//
//char* base64_encode(const char* bytes_to_encode, unsigned int in_len) 
//{
//	
//	BIO *bio, *b64;
//	char message[] = "Hello World \n";
//	char *out;
//	out=(char*)calloc(in_len+128,1);
//	b64 = BIO_new(BIO_f_base64());
//	bio = BIO_new_p(out, BIO_NOCLOSE);
//	BIO_push(b64, bio);
//	BIO_write(b64, bytes_to_encode, in_len);
//	BIO_flush(b64);
//
//	BIO_free_all(b64);
//
//}
//
//char* base64_decode(const char* encoded_string) 
//{
//	BIO *bio, *b64, *bio_out;
//	char inbuf[512];
//	char *out;
//	int inlen;
//	out=(char*)calloc(1024,1);
//
//	b64 = BIO_new(BIO_f_base64());
//	bio = BIO_new_fp(encoded_string, BIO_NOCLOSE);
//	bio_out = BIO_new_fp(out, BIO_NOCLOSE);
//	BIO_push(b64, bio);
//	while((inlen = BIO_read(b64, inbuf, 512)) > 0) 
//		BIO_write(bio_out, inbuf, inlen);
//
//	BIO_flush(bio_out);
//	BIO_free_all(b64);
//}


unsigned char key[AES_BLOCK_SIZE*2]={-123, 29, 32, -6, -76, -96, -118, 120, 21, -121, -13, 25, -55, -94, -19, 11, -66, -65, -41, 43, -106, -43, 119, 106, 107, -24, -87, 121, 105, 63, 0, -51};
unsigned char iv[AES_BLOCK_SIZE]={65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80};

/**AES ECB模式加密**/
int openssl_aes_ecb_encrypt(char* in, size_t len, char* out)
{
	int i;
	int blockNum;
	int aesInLen;
	char* aesIn;

	AES_KEY aes;

    if(AES_set_encrypt_key(key, 128, &aes) < 0)
    {
        return -1;
    }

	//
	if((len%AES_BLOCK_SIZE)!=0)
	{
		blockNum=len/AES_BLOCK_SIZE+1;
		aesInLen=blockNum*AES_BLOCK_SIZE;
		aesIn=(char*)calloc(aesInLen,1);
		memcpy(aesIn,in,len);
		//for(i=len;i<blockNum*AES_BLOCK_SIZE;i++)
		//	aesIn[i]='0';
	}
	else
	{
		blockNum=len/AES_BLOCK_SIZE;
		aesInLen=len;
		aesIn=(char*)calloc(aesInLen,1);
		memcpy(aesIn,in,len);
	}
	
	/**由于ECB每次只处理AES_BLOCK_SIZE大小的数据，所以要通过循环来完成所有数据对加密，解密也是一样的道理**/
	for(i=0;i<blockNum;i++)
	{
		AES_ecb_encrypt((unsigned char*)aesIn,(unsigned char*)out,&aes,AES_ENCRYPT);
		aesIn+=AES_BLOCK_SIZE;
		out+=AES_BLOCK_SIZE;
	}

    return aesInLen;
}
/**AES ECB模式解密**/
int openssl_aes_ecb_decrypt(char* in,size_t len, char* out)
{
	unsigned int i;
	AES_KEY aes;

    if(AES_set_decrypt_key(key, 128, &aes) < 0)
    {
        return -1;
    }
	
	for(i=0;i<len/AES_BLOCK_SIZE;i++)
	{
		AES_ecb_encrypt((unsigned char*)in, (unsigned char*)out,  &aes, AES_DECRYPT);
		in+=AES_BLOCK_SIZE;
		out+=AES_BLOCK_SIZE;
	}

    return 0;
}