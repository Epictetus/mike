#ifndef _MIKE_NET_H_
#define _MIKE_NET_H_

#include <curl/curl.h>
#include <string>
#include <map>
#include "mike.h"

namespace mike {
  namespace net
  {
    using namespace std;
    using namespace v8;

    void Initialize();
    
    class Curl
    {
    private:
      CURLcode code;
      CURL *conn;
      char errorBuffer[CURL_ERROR_SIZE];
      string buffer;
      string url;
      map<string,string> headers;
      bool InitConn();
      bool Read();
    public:
      Curl(string url, map<string,string> headers);
      ~Curl();
      string Content();
      char* Error();
      bool IsOK();
      static Curl* Open(string url, map<string,string> headers);
    };

    namespace uri
    {
      Handle<Value> Open(const Arguments &args);
    }
  }
}

#endif /* _MIKE_NET_H_ */
