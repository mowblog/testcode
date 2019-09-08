#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define true 1
#define false 0
#define QLEN 4

struct queue
{
	char chq[QLEN];
	unsigned qmem;
};

int Inqueue(struct queue *ch, char cht)
{
	int i;
	if(ch->qmem==QLEN)
		return 0;
	for(i=0;i<QLEN-1;i++)
		ch->chq[i]=ch->chq[i+1];
	ch->chq[QLEN - 1] = cht;
	ch->qmem++;
	return ch->qmem;
}

int Outqueue(struct queue *ch)
{
	int i;
	int cht=ch->chq[0];
	ch->chq[0] = 0;

	ch->qmem--;
	return cht;
}

void Shakespeare(void)
{
	char cht;
	struct queue *ch;
	unsigned i=0;
	int w_len=0;
	FILE *fp;
	if((fp=fopen("Shakespeare.txt","w+"))==NULL)
	{
		printf("can't open Shakespeare.txt, please chteck the FileSystem\n");
		exit(0);
	}
	ch = (struct queue*)calloc(1,sizeof(struct queue));

	srand((int)time(0));
	while(true)
	{
sw2:
	cht=rand()%29;

sw:
		switch(cht)
		{
			case 26: //space
				if(ch->chq[3]==46 || isalpha(ch->chq[3]))
				{
					if (ch->qmem == QLEN)
					{
						cht = Outqueue(ch);
						putchar(cht);
						fputc(cht, fp);
					}
					cht=32;  
					Inqueue(ch,cht);
					w_len=0;
				}else
				 continue;
				break;
			
			case 27: //dot
				if(isalpha(ch->chq[3]))
				{
					cht=46;
					Inqueue(ch,cht);
				
					if (ch->qmem == QLEN)
					{
						cht = Outqueue(ch);
						putchar(cht);
						fputc(cht, fp);
					}

					cht = 32;
					Inqueue(ch, cht);
					w_len = 0;
				}else
					continue;
				break;
			case 28: //LF
				if(ch->chq[3]==32 && ch->chq[2]==46)
				{	
					cht=10; 
					Inqueue(ch,cht);
					w_len=0;
				}else
					continue;
				break;				
			default: //alpha
				cht+=97;
				if (ch->chq[3] == 10 || (ch->chq[2] == 46) && (ch->chq[3] == 32) ||(ch->qmem==0))
					cht = toupper(cht);

				Inqueue(ch, cht);
				w_len++;
				if(w_len>=26)
				{
					cht=26;
					goto sw;
				}
				break;
		}

		if(ch->qmem==QLEN)
		{
			cht=Outqueue(ch);
			putchar(cht);
			fputc(cht,fp);
		}
	}

	fclose(fp);
}

int main()
{
	Shakespeare();
}

