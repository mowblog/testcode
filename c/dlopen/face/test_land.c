#include<stdio.h>
#include<face/faceall_sdk.h>
#include<stdlib.h>
#include <dlfcn.h>

int main(int argc, char** argv){
	//faceall_facesdk_landmark5_get_instance();
	void *handle;
	int (*test)(int);
	char *error;

	handle = dlopen("./libcaffe.so",RTLD_LAZY);
	if(!handle){
		fputs(dlerror(), stderr);
		exit(1);
	}

	test = dlsym(handle, "faceall_facesdk_landmark5_get_instance");
	if((error=dlerror())!=NULL){
		fputs(error,stderr);
		exit(1);
	}

	printf("return from so: %d\n", test(23));
	dlclose(handle);
	return 0;
}
