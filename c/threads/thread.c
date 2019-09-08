#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *threadfun1()
{
int fsel=0;
char *src;

while(1){
	src=(char *)malloc(100);
	if(src==NULL){
		printf("%lu malloc failed\n",pthread_self());
		pthread_exit((void *)-1);
	}
	memset(src,'A',100);
	
	if(fsel==0){
		printf("printf mesg from thread %lu\n",pthread_self());
		fsel=1;
	}
	else{
		fprintf(stdout,"fprintf mesg from thread %lu\n",pthread_self());
		fsel=0;
	}
	sleep(5);
	free(src);
	}
}

void *threadfun2()
{
int fsel=0;
char *src;

while(1){
	src=(char *)malloc(100);
	if(src==NULL){
		printf("%lu malloc failed\n",pthread_self());
		pthread_exit((void *)-1);
	}
	memset(src,'A',100);
	
	if(fsel==0){
		printf("printf mesg from thread %lu\n",pthread_self());
		fsel=1;
	}
	else{
		fprintf(stdout,"fprintf mesg from thread %lu\n",pthread_self());
		fsel=0;
	}
	sleep(5);
	free(src);
	}
}

void *threadfun3()
{
int fsel=0;
char *src;

while(1){
	src=(char *)malloc(100);
	if(src==NULL){
		printf("%lu malloc failed\n",pthread_self());
		pthread_exit((void *)-1);
	}
	memset(src,'A',100);
	
	if(fsel==0){
		printf("printf mesg from thread %lu\n",pthread_self());
		fsel=1;
	}
	else{
		fprintf(stdout,"fprintf mesg from thread %lu\n",pthread_self());
		fsel=0;
	}
	sleep(5);
	free(src);
	}
}

int main()
{
	pthread_t pt1,pt2,pt3;
	pid_t pid1;
	int err;
	
	err = pthread_create(&pt1,NULL,threadfun1,NULL);
	if(err!=0){
		printf("in %lu create thread1 failed\n",getpid());
		return err;
	}
	else
		printf("in %lu thread %lu created\n",getpid(),pt1);
		
	err = pthread_create(&pt2,NULL,threadfun2,NULL);
	if(err!=0){
		printf("in %lu create thread2 failed\n",getpid());
		return err;
	}
	else
		printf("in %lu thread %lu created\n",getpid(),pt2);
		
	err = fork();
	if(err<0){
		printf("in %lu process create failed\n",getpid());
		return err;
	}else if(err==0){
		err = pthread_create(&pt3,NULL,threadfun3,NULL);
		if(err!=0){
			printf("in %lu create thread3 failed\n",getpid());
			return err;
		}
		else
			printf("in %lu thread %lu created\n",getpid(),pt3);
		while(1)
		{sleep(5);}
	}


		sleep(5);

}