#include "libpydll.h"

int pchar_ppchar_t(char* input,char** output)
{
	if(DEBUG)fprintf(stderr,"DEBUG-pchar_ppchar_t:%s\n",input);
	*output=(char*)malloc(O_SIZE);
	memset(*output,'\0',O_SIZE);
	memcpy(*output,input,strlen(input));
	if(DEBUG)fprintf(stderr,"DEBUG-pchar_ppchar_t:%s\n",*output);
	return 0;
}

int pchar_pchar_t(char* input,char* output)
{
        if(DEBUG)fprintf(stderr,"DEBUG-pchar_pchar_t:%s\n",input);
        memcpy(output,input,strlen(input));
        if(DEBUG)fprintf(stderr,"DEBUG-pchar_pchar_t:%s\n",output);
		return 0;
}


