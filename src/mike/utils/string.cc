#include <stdio.h>
#include <string.h>
#include "mike/utils/string.h"

char* strrtrim(char* string, char junk/*=' '*/)
{
  char* original = string + strlen(string);
  while(*--original == junk);
  *(original+1) = '\0';
  return string;
}
      
char* strltrim(char *string, char junk/*=' '*/)
{
  char* original = string;
  char *p = original;
  int trimmed = 0;

  do {
    if (*original != junk || trimmed) {
      trimmed = 1;
      *p++ = *original;
    }
  }
  
  while (*original++ != '\0');
  return string;
}

char* strtrim(char *string, char junk/*=' '*/)
{
  return strrtrim(strltrim(string, junk), junk);
}
