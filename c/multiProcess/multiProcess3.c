#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int p_count=0;
	int c_count1=0,c_count2=0;
	
	if(fork()==0)
	{
		while(c_count1 < 1000)
		{
			printf("this is child1(%d)-(%d):%d\n",getppid(),getpid(), c_count1++);
			sleep(1);
		}
		return 0;
	}
	else
	{
		if(fork()==0)
		{
			while(c_count2 < 1000)
			{
				printf("this is child2(%d)-(%d):%d\n",getppid(),getpid(), c_count2++);
				sleep(1);
			}
			return 0;
		}
		else{
		while(p_count < 1000)
		{
			printf("this is parent(%d)-(%d):%d\n",getppid(), getpid(), p_count++);
			sleep(1);
		}
		}
	}
	return 0;
}
