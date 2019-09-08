#ifndef _LIBPYDLL_H_
#define _LIBPYDLL_H_
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define O_SIZE 1024
#define DEBUG 0

#ifdef __cplusplus
extern "C" {
#endif
int __declspec(dllexport) __stdcall pchar_ppchar_t(char* ,char** );
int __declspec(dllexport) __stdcall pchar_pchar_t(char* ,char* );
#ifdef __cplusplus
}
#endif