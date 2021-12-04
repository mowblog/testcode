#include "myunp.h"

int 
main(int argc,char* argv[])
{
	int sockfd,n;
	char recvline[MAXLINE + 1], sendline[MAXLINE];
	
	#if defined AF6
	struct sockaddr_in6 servaddr;
	#else
	struct sockaddr_in servaddr;
	#endif
	
	if(argc != 3)
	{
		printf("%s\n","usage: tcpc <Server IP> <Server Port>");
		return 0;
	}
	
	bzero(&servaddr,sizeof(servaddr));
	#ifdef AF6
	RUN((sockfd=socket(AF_INET6,SOCK_STREAM,0)),"socket");

	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_port = htons(atoi(argv[2]));
	RUN(inet_pton(AF_INET6,argv[1],&servaddr.sin6_addr), "inet_pton");

	#else
	RUN((sockfd=socket(AF_INET,SOCK_STREAM,0)), "socket");

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	RUN(inet_pton(AF_INET,argv[1],&servaddr.sin_addr), "inet_pton");

	#endif
	
	RUN(connect(sockfd, (SA *)&servaddr, sizeof(servaddr)), "connect");
	
	snprintf(sendline, MAXLINE, "%s", "hello");
	//if(write(sockfd, sendline, strlen(sendline)) < 0)
	RUN(send(sockfd, sendline, strlen(sendline), 0), "send");

	/*
	while( (n = read(sockfd, recvline, MAXLINE)) > 0)
	{
		recvline[n] = 0;
		if(fputs(recvline, stdout) == EOF)
			err_exit("fputs");
		if(n < 0)
			err_exit("read");
		exit(0);	
	}
	*/
	RUN(recv(sockfd, recvline, MAXLINE, 0), "recv");

	fputs(recvline, stdout);	
	close(sockfd);
	
	sleep(5); //sleep��Ϊ�����tcp�رյĹ��̣���������TIME_WAIT��״̬
}

/**
 storage size of ��servaddr�� isn��t known
 
**/
