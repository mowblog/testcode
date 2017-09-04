#include <stdio.h>
#include <wchar.h>

int main()
{
        char *str;
        int i;
        size_t length=100;
        str=(char*)malloc(length);
        scanf("%s",str);
        printf("%s\n",str);
        for(i=0;i<strlen(str);i++)
        {
                printf("%X ",str[i]);
        }
        printf("\n");

}