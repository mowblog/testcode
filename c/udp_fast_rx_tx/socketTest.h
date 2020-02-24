#ifndef _socket_Test_h_
#define _socket_Test_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h> /* basic socket definitions */
#include <netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/socket.h>

//#define __DEBUG__  
#ifdef __DEBUG__  
#define DEBUG(format,...) fprintf(stderr,"File: "__FILE__", Line: %05d: "format"\n", __LINE__, ##__VA_ARGS__)  
#else  
#define DEBUG(format,...)  
#endif  

#define COLLECT_COUNT 10002

void getSocketOpts(int sockfd)
{
    struct timeval timeVal = {0};  
    int optLen = sizeof(int);  
    getsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,(void *)&timeVal, (socklen_t *)&optLen);
    fprintf(stdout,"SO_RCVTIMEO: %ld\n", timeVal.tv_sec*1000000+timeVal.tv_usec);
}

#endif