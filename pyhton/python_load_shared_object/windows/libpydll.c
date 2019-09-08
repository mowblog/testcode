#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define O_SIZE 1024
#define DEBUG 0

#ifdef __cplusplus
extern "C" {
#endif
int __declspec(dllexport) __stdcall pchar_ppchar_t(char* input,char** output)
{
	if(DEBUG)fprintf(stderr,"DEBUG-%s\n",input);
	*output=(char*)malloc(O_SIZE);
	memset(*output,'\0',O_SIZE);
	memcpy(*output,input,strlen(input));
	if(DEBUG)fprintf(stderr,"DEBUG-%s\n",*output);
	return 0;
}

int __declspec(dllexport) __stdcall pchar_pchar_t(char* input,char* output)
{
        if(DEBUG)fprintf(stderr,"DEBUG-%s\n",input);
        memcpy(output,input,strlen(input));
        if(DEBUG)fprintf(stderr,"DEBUG-%s\n",output);
		return 0;
}
#ifdef __cplusplus
}
#endif
