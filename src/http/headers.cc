#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "http/headers.h"

namespace mike {
  namespace http {
    namespace
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
    }
    
    Headers::Headers()
    {
    }

    Headers::~Headers()
    {
    }

    void Headers::parseAndAppend(string line)
    {
      int splitter = line.find(':');
      
      if (splitter > 0) {
	string key = strstrip(line.substr(0, splitter));
	string value = strstrip(line.substr(splitter+1));

	map<string,string>::iterator it = headers_.find(key);
	
	if (it != headers_.end()) {
	  it->second.append("\n"+value);
	} else {
	  headers_[key] = value;
	}
      }
    }
    
    map<string,string> Headers::toMap()
    {
      return headers_;
    }
    
    void Headers::clear()
    {
      headers_.clear();
    }
  }
}
