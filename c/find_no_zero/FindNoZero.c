/*
FindNoZero
*/
#include "stdio.h"
#include "stdlib.h"

void enter()
{
printf("Press enter to exit\n");
getch();
}

int main(int argc, char* argv[])
{
	FILE* fp1;
	char ch[1];
	if(argc<2){
	printf("Please use like this: FindNoZero.exe fillname \n");
	enter();
	return -1;
	}
	if((fp1=fopen(argv[1], "rb"))==NULL){
		printf("file %s open failed\n",argv[1]);
		fclose(fp1);
	}
	else while(feof(fp1)==0)
		{
			fread(ch,1,1,fp1);
			if(ch[0]!=0){
			printf("%x\toffset is 0x%x:\n",ch[0], ftell(fp1));
			}
			else{
			}
		}
	fclose(fp1);
	enter();
}


