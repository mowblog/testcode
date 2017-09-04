#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	unsigned long cNum=0;
	unsigned long sNum=0;
	unsigned long rNum=0;
	unsigned long oNum=0;
	char ch;
	FILE* fp;
	if(argc != 2)
	{
		printf("Please specify the text file to continue\n");
		exit(0);
	}

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Can't open %s to read\n",argv[1]);
		exit(0);
	}

	while((ch=fgetc(fp))!=EOF)
	{
		if(isalpha(ch)||isdigit(ch))
			cNum++;
		else if(isspace(ch))
			sNum++;
		     else 
			oNum++;
	}
	fclose(fp);
	printf("total characters are: %u\nspace: %u\tother: %u\tcharacter: %u\n",sNum+cNum+oNum,sNum,oNum,cNum);
	return 0;
}
