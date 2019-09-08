#include "mysock.h"

void err_exit(char *msg)
{
	printf("%s: %d\n",msg,WSAGetLastError());
	exit(1);
}

int wsa_init()
{
	int err;
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD( 2, 2 );

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		printf("WSAStartup: %d\n",err=WSAGetLastError());
		exit(err);
	}

	/*
	if ( LOBYTE( wsaData.wVersion ) != 1 ||	HIBYTE( wsaData.wVersion ) != 1 ) 
	{
		printf("little or big error\n");
		WSACleanup( );
		exit(1); 
	}
	*/
	return 0;
}

int tcp_keep_alive(int socketfd)
{
	int keepAlive = 1;
	int keepIdle = 10;
	int keepInterval = 10;
	int keepCount = 10;

	if(setsockopt(socketfd,SOL_SOCKET,SO_KEEPALIVE,(char*)&keepAlive,sizeof(keepAlive)) == -1){
		printf("setsockopt SIO_KEEPALIVE_VALS failed\n");
		return -1;
	}
	return 0;
}