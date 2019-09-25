#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void func1(char* username, char* password)
{
    // fprintf(stdout,"username: %s\npassword: %s\n", username, password);
    ;
}

void main()
{
    char sec_mem[1024] = {0};
    char *username;
    char *password;

    username = sec_mem;
    password = sec_mem+100;

    fprintf(stdout,"input username:\n");
    scanf("%s",username);
    fprintf(stdout,"input password:\n");
    scanf("%s",password);

    func1(username, password);

    memset(sec_mem, 0, 1024);
    while(1)
    {
        sleep(20);
    }
}