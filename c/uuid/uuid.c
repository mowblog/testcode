#include <stdio.h>
#include <uuid.h>


int
main()
{
	int status;
	uuid_t *uuid;
	char uuid_s[128];
	//bzero((struct uuit_t*)&uuid,sizeof(uuid));
	//uuid_generate(&uuid);
	status=uuid_create(&uuid);
	status=uuid_to_string(uuid, &uuid_s,&status);
	fprintf(stdout,"%s\n",uuid_s);
	printf("\n");		
}
