#ifndef _MIKE_UTILS_STRING_H_
#define _MIKE_UTILS_STRING_H_

#include <stdio.h>

char* strrtrim(char* string, char junk=' ');
char* strltrim(char *string, char junk=' ');
char* strtrim(char *string, char junk=' ');

#define trim strtrim
#define ltrim strltrim
#define rtrim strrtrim

#endif /* _MIKE_UTILS_STRING_H_ */
