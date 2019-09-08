#include <syslog.h>
#include <stdio.h>

void main()
{	
	//write log into var/log/syslog
	syslog(LOG_ERR,"this is a syslog test...\n");
}