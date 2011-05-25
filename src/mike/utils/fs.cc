#include <stdio.h>
#include <stdlib.h>

#include "mike/utils/fs.h"

namespace mike
{
  /**
   * Reads file contents and returns it. If file can't be open or read
   * then returns NULL. 
   *
   *   char *content = mike::ReadFile("foo/bar.txt");
   *   assert(content != NULL);
   *
   * @param name: name of file to read
   */
  char* ReadFile(const char *name)
  {
    FILE *fp = fopen(name, "rb");

    if (fp == NULL) {
      return NULL;
    }
                    
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    rewind(fp);

    char *chars = new char[size+1];
    chars[size] = '\0';
    int pos = 0;
    
    while (pos < size) {
      pos += fread(&chars[pos], 1, size-pos, fp);
    }
                
    fclose(fp);
    return chars;
  }
}
