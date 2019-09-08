#ifndef __MYSOCK_H
#define __MYSOCK_H
#endif

#include <Winsock2.h>
#include <Ws2tcpip.h> //contain inet_pton()
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define	MAXLINE		4096
#define	SA	struct sockaddr

#define AF4 /**/

#define RUN(A,B) if((A) < 0)err_exit(B)
#define bzero(a, b)  memset(a, 0, b)

extern int wsa_init(void);
extern void err_exit(char* msg);