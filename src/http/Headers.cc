#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "http/Headers.h"
#include "utils/Helpers.h"

namespace mike {
  namespace http {    
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
