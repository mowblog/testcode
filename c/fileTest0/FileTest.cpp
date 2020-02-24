// FileTest.cpp : Defines the entry point for the console application.
//

#include "stdio.h"
#include "stdlib.h"

void enter()
{
printf("Press enter to exit\n");
getchar();
}

int main(int argc, char* argv[])
{
	FILE* fp1;
	char ch[1];
	if(argc<2)
	{
	printf("Please input the file name\n");
	enter();
	return -1;
	}

	if((fp1=fopen(argv[1], "rb"))==NULL)
	{
		printf("file open failed\n");
		fclose(fp1);
	}
		else while(feof(fp1)==0)
		{
			fread(ch,1,1,fp1);
			if(ch[0]!=0)
			{
			printf("%x\toffset is 0x%x:\n",ch[0], ftell(fp1));
			}
		
		}
	fclose(fp1);
	enter();
	return 0;
}