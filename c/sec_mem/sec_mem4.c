#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "base64.h"

void func1(char* username, char* password)
{
    ;
}

void main()
{
    char sec_mem[1024] = {0};
    char *username;
    char *password;

    username = sec_mem;
    password = sec_mem+100;

    Base64decode(username, "emhhbmdzYW4=");
    Base64decode(password, "bGlzaQ==");

    func1(username, password);

    memset(sec_mem, 0, 1024);
    while(1)
    {
        sleep(20);
    }
}

/*
https://opensource.apple.com/source/QuickTimeStreamingServer/QuickTimeStreamingServer-452/CommonUtilitiesLib/
*/