#include <string.h>
#include "utils/Helpers.h"

namespace mike
{
  char *strstrip(string value)
  {
    char* s = (char*)value.c_str();
    size_t size = strlen(s);
    
    if (!size) {
      return s;
    }
    
    char *end = s + size -1;
    
    while (end >= s && isspace(*end)) {
      end--;
    }
    
    *(end + 1) = '\0';
    
    while (*s && isspace(*s)) {
      s++;
    }
    
    return s;
  }

  string strjoin(string parts[], int size, string separator/*=""*/)
  {
    string result = "";

    if (size > 0) {
      result += parts[0];
      
      for (int i = 1; i < size; i++) {
	result += separator;
	result += parts[i];
      }
    }

    return result;
  }

  string xpathSanitize(string arg)
  {
    char find[3] = { '&', '"', '\'' };
    string replace[3] = { "&amp;", "&quot;", "\\'" };

    for (int i = 0; i < 3; i++) {
      string right = arg;
      int split = 0;
      
      arg = "";
      
      while ((split = right.find(find[i])) > 0) {
	arg += right.substr(0, split);
	arg += replace[i];
	right = right.substr(split+1);
      }

      arg += right;
    }

    return arg;
  }
}
