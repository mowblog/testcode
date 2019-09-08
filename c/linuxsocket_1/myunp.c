#include "myunp.h"
#include <errno.h>

void err_exit(char *msg)
{
	perror(msg);
	exit(1);
}
