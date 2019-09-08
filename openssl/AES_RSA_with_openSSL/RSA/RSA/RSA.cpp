#include<string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

#pragma comment(lib,"libeay32.lib")
#pragma comment(lib,"ssleay32.lib")

int main(int argc, char* argv[])
{
	int ret=0;

	char in[16]={'1','2','3','4','5','6','7','8','9','0','a','b','c','d','e','f'};
	char out[1024]={0};

	RSA *rsa=NULL,*pub_rsa=NULL,*pri_rsa=NULL ;
	int bits=2048;
	BIGNUM *b=NULL;
	unsigned long e=RSA_F4;
	BIO *bp_public = NULL, *bp_private = NULL;
    //RSA* pRsa = RSA_generate_key( 1024 ,RSA_F4,0,0);
	b=BN_new();
	ret=BN_set_word(b,e);
	rsa=RSA_new();
	RSA_generate_key_ex(rsa, bits, b, NULL);

    bp_public = BIO_new_file("public.pem", "w+");
	ret = PEM_write_bio_RSAPublicKey(bp_public, rsa);
	bp_private = BIO_new_file("private.pem", "w+");
    ret = PEM_write_bio_RSAPrivateKey(bp_private, rsa, NULL, NULL, 0, NULL, NULL);


	int len = RSA_size(rsa);
	unsigned char *p=new unsigned char[len];
    memset(p,0,len);
    RSA_public_encrypt( sizeof(in) , (unsigned char *)in , p , rsa ,  RSA_PKCS1_PADDING );
    
    RSA_private_decrypt( len , p , (unsigned char *)out , rsa , RSA_PKCS1_PADDING );
    printf("%s\n",out);
    RSA_free( rsa );

	FILE* fp;
	char out2[1024];
	fp = fopen("private.pem", "r");
	pri_rsa = PEM_read_bio_RSAPrivateKey(bp_private,NULL,NULL,NULL);
	//pri_rsa = PEM_read_RSAPrivateKey(fp,NULL,NULL,NULL);
	RSA_private_decrypt( len , p , (unsigned char *)out2 , pri_rsa , RSA_PKCS1_PADDING );
	printf("%s\n",out2);


	memset(out,0,1024);

	fp = fopen("public.pem", "r");
	if(fp==NULL)
	{
		printf("open public.pem failed\n");
	}
		b=BN_new();
	ret=BN_set_word(b,e);
	//pub_rsa = PEM_read_bio_RSAPublicKey(bp_public,NULL,NULL,NULL);
	RSA *tmp;
	pub_rsa = PEM_read_RSA_PUBKEY(fp,&tmp,NULL,NULL);
	//pub_rsa = PEM_read_RSAPublicKey(fp,NULL,NULL,NULL);
	if(pub_rsa==NULL)
	{
		printf("init public key failed\n");
		return 0;
	}
	unsigned char* p2=new unsigned char[sizeof(pub_rsa)];
	RSA_print_fp(stdout, pub_rsa, 0);
	RSA_public_encrypt( sizeof(in) , (unsigned char *)in , p , pub_rsa ,  RSA_PKCS1_PADDING );
	fclose(fp);



    return 0;
	//获取/设置RSA的公钥和私钥
}

/**
http://www.codepool.biz/tech-frontier/how-to-use-openssl-generate-rsa-keys-cc.html
**/