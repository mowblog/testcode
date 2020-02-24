#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char** environ;

int main(int argc, char* argv[])
{
 int i=0,j;
 char** ptr;
 ptr = environ;
 while((*ptr)!=NULL){
 i++;
 printf("%d - %s\n",i,*ptr);
 (*ptr) += strlen(*ptr);
 sleep(1);
}
}
