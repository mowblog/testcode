#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "aes.h"

#pragma comment(lib,"libeay32.lib")
#pragma comment(lib,"ssleay32.lib")

void usage();

int main(int argc,char *argv[])
{
	char offset[4]={'0'}; /**用于存放填充字节数的数组**/
	char *src,*dst;
	int inlen,outlen,size;
	FILE *srcFile;
	FILE *dstFile;

	if(argc!=5)
	{
		usage();
		return 0;
	}
	if((srcFile=fopen(argv[3],"rb"))==NULL)
	{
		printf("open srcFile failed\n");
		return -1;
	}

	if((dstFile=fopen(argv[4],"wb+"))==NULL)
	{
		printf("open dstFile failed\n");
		return -2;
	}

	fseek(srcFile,0,SEEK_END);
	inlen=ftell(srcFile); /**获取输入文件的大小**/
	if(inlen<0)
	{
		printf("srcFile operate failed\n");
	}
	fseek(srcFile,0,SEEK_SET); /**返回文件开始**/
	
	argv[2]++;
	switch(argv[2][0])
	{
		case 'e'|'E':
			src=(char*)calloc(inlen,1);
			size=fread(src,1,inlen,srcFile);
			printf("input %d byte\n",size);
			outlen=(inlen/16+1)*16; /**输出变量申请的空间额外增加16字节，防止出错**/
			dst=(char*)calloc(outlen,1);
			if(strcmp(argv[1],"-cbc")==0)
			{
				size=openssl_aes_cbc_encrypt(src,inlen,dst);
				sprintf(offset,"%d",size-inlen); /**获取填充的字节数,记录到输出文件的前4个字节内**/
				fwrite(offset,sizeof(char),4,dstFile);
			}
			else if(strcmp(argv[1],"-ecb")==0)
			{
				size=openssl_aes_ecb_enrypt(src,inlen, dst);
				sprintf(offset,"%d",size-inlen);
				fwrite(offset,sizeof(char),4,dstFile);
			}
			else{
				usage();
				return 0;
			}
			break;
		case 'd'|'D':
			fread(offset,sizeof(char),4,srcFile);
			inlen-=4;
			src=(char*)calloc(inlen,1);
			size=fread(src,1,inlen,srcFile); /**从加密后的文件中获取填充的字节数，用于恢复原始文件**/
			printf("input %d byte\n",size);
			size=size-atoi(offset); 	/**得到原始文件的大小**/
			
			outlen=(inlen/16+1)*16;
			dst=(char*)calloc(outlen,1);
			if(strcmp(argv[1],"-cbc")==0)
			{
				openssl_aes_cbc_decrypt(src,inlen,dst);
			}
			else if(strcmp(argv[1],"-ecb")==0)
			{
				openssl_aes_ecb_decrypt(src,inlen,dst);
			}
			else{
				usage();
				return 0;
			}
			break;
		default:
			usage();
			break;
	}

	size=fwrite(dst,1,size,dstFile); /**输出加密后的文件或者解密后的文件，由于size已经做了调整，
										所以解密后的文件大小和原始文件应该一致**/
	printf("output %d byte\n",size);
	fclose(srcFile);
	fclose(dstFile);
	free(src);
	free(dst);
}

void usage()
{
	printf("aes -cbc/-ecb -e/-d input output\n		");
	getc(stdin);
}