#include<stdio.h>

int
main()
{
	#ifdef AF6
	printf("AF6 defined\n");
	#else
	printf("use AF4 as default\n");
	#endif
}
