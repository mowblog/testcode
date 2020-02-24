#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char* argv[])
{
	void *handle;
//	int (*test)(int);
	char *error;
	typedef int (*ttt)(int);

	handle = dlopen("./libtest_p.so",RTLD_LAZY);
	if(!handle){
		fputs(dlerror(), stderr);
		exit(1);
	}

	ttt test =(ttt) dlsym(handle, "test");
	if((error=dlerror())!=NULL){
		fputs(error,stderr);
		exit(1);
	}

	printf("return from so: %d\n", test(23));
	dlclose(handle);

}
