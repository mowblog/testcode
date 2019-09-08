#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SLEEPTIME 72000 //10 hours
#define THREAD_NUM 10
#define ARRAY_SIZE 50000
#define COUNT 2000
#define M 6000
#define N 8000

struct tmp
{
	struct tmp *pre;
	struct tmp *next;
	char nothing[1<<20];
};
int mb=0;
FILE *fp;

int memtest(struct tmp *head,int c,FILE *fp)
{
	struct tmp *p;
	p = (struct tmp *)malloc(sizeof(struct tmp));
	if(p==NULL){
		printf("cannot malloc memory anymore\n");
		return c;
	}else{
		c++;
		//printf("Allocated %d MB\n",mb);
		}
	head->next = p;
	memset(head->nothing,'A',sizeof(head->nothing));
	if(c<COUNT)
		memtest(p,c,fp);
	else
		printf("process %d Allocated %d MB\n",getpid(), c);
/*
	while(c<=COUNT)
	{
		void* memtmp = malloc(1<<20);
		c++;
	}
	fprintf(stdout,"process %d Allocated %d MB\n",getpid(), c);
*/	
	return c;
}

void *threadfun()
{	
	while(1)
	{
		srand((int)time(0));
		double j = pow(rand()%M,rand()%N);
		double k = sqrt(rand());
		double l = log(rand());

	}
	
}

int main(int argc,char *argv[])
{
	pid_t pid1,pid2,pid3;
	int timer1,timer2,timer3;
	pthread_t tid[THREAD_NUM];
	int err;
	int i;
	int c1,c2,c3;
	struct tmp *head1, *head2, *head3;
	
	
	if((fp=fopen("mfile","rb"))==NULL)
	{
		printf("open file failed,exit...\n");
		exit(-1);
	}
	
	if((pid1 = fork())<0)
		printf("create child process 1 failed\n");
	else if(pid1==0){
		timer1=0;
		printf("process1 %d start------\n",getpid());
		head1 = (struct tmp *)malloc(sizeof(struct tmp));
		c1=0;
		err = memtest(head1,c1,fp);
		for(i=0;i<THREAD_NUM;i++){
		err = pthread_create(&tid[i],NULL,threadfun,NULL);
		if(err!=0)
			printf("thread %d create failed\n",i+1);
		}
		while(timer1<SLEEPTIME)
		{
			sleep(1);
			timer1++;
		}
		printf("canceling threads....\n");
		for(i=0;i<THREAD_NUM;i++){
		err = pthread_cancel(tid[i]);
		if(err!=0)
			printf("thread %d cancel failed\n",i+1);
		}
		sleep(5);
		printf("process1 %d end------\n",getpid());
		exit(0);
	}
	printf("process1 %d with threads created\n",pid1);
	
	if((pid2 = fork())<0)
		printf("create child process 2 failed\n");
	else if(pid2==0){
		timer2=0;
		printf("process2 %d start------\n",getpid());
		head2 = (struct tmp *)malloc(sizeof(struct tmp));
		c2=0;
		err = memtest(head2,c2,fp);
		while(timer2<SLEEPTIME)
		{
			sleep(1);
			timer2++;
		}
		printf("process2 %d end------\n",getpid());
		exit(0);
	}
	printf("process2 %d created\n",pid2);
	
	if((pid3 = fork())<0)
		printf("create child process 2 failed\n");
	else if(pid3==0){
		timer3=0;
		printf("process3 %d start------\n",getpid());
		head3 = (struct tmp *)malloc(sizeof(struct tmp));
		c3=0;
		err = memtest(head3,c3,fp);
		while(timer3<SLEEPTIME)
		{
			sleep(1);	
			timer3++;
		}	
		printf("process3 %d end------\n",getpid());
		exit(0);
	}
	printf("process3 %d created\n",pid3);

	exit(0);

}
