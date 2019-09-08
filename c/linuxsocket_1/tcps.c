#include "myunp.h"
#include <time.h>

int
main(int argc, char* argv[])
{
	int listenfd, connfd;
	int addrlen;
	#ifdef AF4
	struct sockaddr_in servaddr, cliaddr;
	#else
	struct sockaddr_in6 servaddr, cliaddr;
	#endif
	
	char sendline[MAXLINE],recvline[MAXLINE];
	time_t ticks;
	
	if(argc != 2)
	{
		printf("%s\n","usage: tcps <Server Port>");
		return 0;
	}
	
	bzero(&servaddr, sizeof(servaddr));
	#ifdef AF4
	listenfd = socket(AF_INET, SOCK_STREAM, 0 );
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1]));
	#else
	listenfd = socket(AF_INET6, SOCK_STREAM, 0 );
	servaddr.sin6_family = AF_INET6;
	//inet_pton(AF_INET6, "::1", &servaddr.sin6_addr); 
	servaddr.sin6_addr = in6addr_any;
	servaddr.sin6_port = htons(atoi(argv[1]));
	#endif
	
	RUN(bind(listenfd, (SA *)&servaddr, sizeof(servaddr)), "bind");
	
	RUN(listen(listenfd, 5), "listen");
	
	addrlen = sizeof(cliaddr);
	for(;;)
	{
		RUN((connfd = accept(listenfd, (SA *)&cliaddr, &addrlen)), "accept");

		//if(read(connfd, recvline, MAXLINE) < 0)
		RUN(recv(connfd, recvline, MAXLINE, 0), "recv");
		
		ticks = time(NULL);
		snprintf(sendline, sizeof(sendline), "%.24s\r\n", ctime(&ticks));
		//if((write(connfd, sendline, strlen(sendline))) < 0)
		RUN(send(connfd, sendline, strlen(sendline), 0), "send");
		
		close(connfd);
	}
}