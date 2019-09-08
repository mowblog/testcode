#include "mysock.h"

#pragma comment(lib,"ws2_32.lib")

int 
main(int argc,char* argv[])
{
	int sockfd,n;
	char sendline[MAXLINE], recvline[MAXLINE];
	#ifdef AF4
	struct sockaddr_in servaddr;
	#else 
	struct sockaddr_in6 servaddr;
	#endif
	
	if(argc != 3)
	{
		printf("%s\n","usage: udpc <Server IP> <Server Port>");
		return 0;
	}
	
	wsa_init();
	
	bzero(&servaddr, sizeof(servaddr));
	#ifdef AF4

	RUN((sockfd = socket(AF_INET, SOCK_DGRAM, 0)),"socket");
	
	servaddr.sin_family = AF_INET;
	//if((inet_pton(AF_INET, argv[1], &servaddr.sin_addr) < 0))
	//	err_exit("inet_pton AF_INET");
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	servaddr.sin_port = htons(atoi(argv[2]));	
	
	#else
	RUN((sockfd = socket(AF_INET6, SOCK_DGRAM, 0)), "socket");
	
	servaddr.sin6_family = AF_INET6;
	RUN(inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr), "inet_pton");
	servaddr.sin6_port = htons(atoi(argv[2]));	
	#endif
	
	_snprintf(sendline, MAXLINE, "%s", "hello");
	RUN(sendto(sockfd, sendline, strlen(sendline), 0, (SA *)&servaddr, sizeof(servaddr)), "sendto");
		
	RUN(recvfrom(sockfd, recvline, MAXLINE, 0 ,(SA *)NULL, NULL), "recvfrom");	

	fputs(recvline, stdout);	
	
	closesocket(sockfd);
}