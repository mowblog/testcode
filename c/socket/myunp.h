#ifndef __myunp_h
#define __myunp_h
#endif

#define	MAXLINE		4096
#define	SA	struct sockaddr

#define AF6 /**/

#define RUN(A,B) if((A) < 0)err_exit(B)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h> /* basic socket definitions */
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */

