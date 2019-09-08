#include "myunp.h"

int 
main(int argc,char* argv[])
{
	int sockfd, n, addrlen;
	char sendline[MAXLINE],recvline[MAXLINE];
	time_t ticks;
		
	if(argc != 2)
	{
		printf("%s\n","usage: udps <Server Port>");
		return 0;
	}
	
	#ifdef AF4
	struct sockaddr_in servaddr, cliaddr;
	#else 
	struct sockaddr_in6 servaddr, cliaddr;
	#endif
		
	bzero(&servaddr, sizeof(servaddr));
	#ifdef AF4
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		err_exit("socket");
		
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	/*
	if((inet_pton(AF_INET, "::1", &servaddr.sin_addr) < 0))
		err_exit("inet_pton AF_INET");
	*/	
	servaddr.sin_port = htons(atoi(argv[1]));	
	#else
	if((sockfd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0) 
		err_exit("socket");
		
	servaddr.sin6_family = AF_INET6;
	/*
	if((inet_pton(AF_INET6, "::1", &servaddr.sin6_addr) < 0))
		err_exit("inet_pton AF_INET6");
	*/	
	servaddr.sin6_addr = in6addr_any;	//ipv6绑定所有地址要这么设置
	servaddr.sin6_port = htons(atoi(argv[1]));	
	#endif

	RUN(bind(sockfd,(SA *)&servaddr,sizeof(servaddr)), "bind");
	
	addrlen = sizeof(cliaddr);	
	for(;;)
	{	
		RUN(recvfrom(sockfd, recvline, MAXLINE, 0 , (SA *)&cliaddr, &addrlen), "recvfrom");

		//fputs(recvline, stdout);
		ticks = time(NULL);
		snprintf(sendline, MAXLINE, "%.24s\r\n", ctime(&ticks));
		RUN(sendto(sockfd, sendline, strlen(sendline), 0, (SA *)&cliaddr, sizeof(cliaddr)), "sendto");
	}
	
	close(sockfd);
}