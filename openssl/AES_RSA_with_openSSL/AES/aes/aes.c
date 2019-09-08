#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "aes.h"

/**DEBUG是一个以16进制打印数据的宏，为了方便调试，具体实现在hexdump里面**/
#define DEBUGFLAG 0
#define DEBUG(str,len) {if(DEBUGFLAG) hexdump((str),(len));}

const unsigned char key[AES_BLOCK_SIZE*2]={-123, 29, 32, -6, -76, -96, -118, 120, 21, -121, -13, 25, -55, -94, -19, 11, -66, -65, -41, 43, -106, -43, 119, 106, 107, -24, -87, 121, 105, 63, 0, -51};
unsigned char iv[AES_BLOCK_SIZE]={65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80};

void hexdump(char* str, size_t len)
{
	unsigned int i;
	unsigned char*p=(unsigned char*)str;
	printf("hexdump %d bytes data:\n",len);
	for(i=1;i<=len;i++)
	{
		printf("%2X  ",p[i]);
		if(i%16==0)
			printf("\n");
	}
	printf("\n");
}
/**AES CBC模式加密**/
int openssl_aes_cbc_encrypt(char* in, size_t len, char* out)
{
	int i;
	AES_KEY aes;
	char* aesIn; /**为了填充数据为AES_BLOCK_SIZE的整数倍，
					单独申请一个变量用于存放填充后的要加密的数据**/
	int blockNum,aesInLen;
    if(AES_set_encrypt_key(key, 256, &aes) < 0) /**设置加密密钥**/
    {
        return -1;
    }
	
	/**判断原始数据长度是否AES_BLOCK_SIZE的整数倍**/
	if((len%AES_BLOCK_SIZE)!=0)
	{
		/**不是整数倍，用'0'填充**/
		blockNum=len/AES_BLOCK_SIZE+1;
		aesInLen=blockNum*AES_BLOCK_SIZE;
		aesIn=(char*)calloc(aesInLen,1);
		for(i=len;i<aesInLen;i++) //PKCS5Padding
			aesIn[len]=(aesInLen-len);
		memcpy(aesIn,in,len);
	}
	else
	{
		aesInLen=len;
		aesIn=(char*)calloc(aesInLen,1);
		memcpy(aesIn,in,len);
	}

	DEBUG(aesIn,aesInLen)
    AES_cbc_encrypt((unsigned char*)aesIn, (unsigned char*)out, aesInLen, &aes, iv, AES_ENCRYPT);
	DEBUG(out,aesInLen)
    return aesInLen; /**返回填充后加密数据的长度**/
}
/**AES CBC模式解密**/
int openssl_aes_cbc_decrypt(char* in, size_t len, char* out)
{
	AES_KEY aes;

    if(AES_set_decrypt_key(key, 256, &aes) < 0)
    {
        return -1;
    }
    DEBUG(in,len)
    AES_cbc_encrypt((unsigned char*)in, (unsigned char*)out, len, &aes, iv, AES_DECRYPT);
	DEBUG(out,len)
    return 0;
}
/**AES ECB模式加密**/
int openssl_aes_ecb_enrypt(char* in, size_t len, char* out)
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
