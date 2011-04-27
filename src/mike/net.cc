#include "mike/net.h"

namespace mike {
  namespace net
  {
    using namespace std;

    namespace
    {
      size_t Writer(char *data, size_t size, size_t nmemb, string *wdata)
      {
	if (wdata == NULL) {
	  return 0;
	}
	
	wdata->append(data, size*nmemb);
	return size*nmemb;
      }
    }

    Curl::Curl(string url)
    {
      this->url = url;

      if (InitConn()) {
	Read();
      }
    }

    Curl::~Curl()
    {
      // nothing...
    }

    bool Curl::InitConn()
    {
      conn = curl_easy_init();
      
      if (conn == NULL) {
	code = (CURLcode)(-1);
	return false;
      }
      if ((code = curl_easy_setopt(conn, CURLOPT_ERRORBUFFER, errorBuffer)) != CURLE_OK) {
	return false;
      }
      if ((code = curl_easy_setopt(conn, CURLOPT_URL, url.c_str())) != CURLE_OK) {
	return false;
      }
      if ((code = curl_easy_setopt(conn, CURLOPT_FOLLOWLOCATION, 1L)) != CURLE_OK) {
	return false;
      }
      if ((code = curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, Writer)) != CURLE_OK) {
	return false;
      }
      if ((code = curl_easy_setopt(conn, CURLOPT_WRITEDATA, &buffer)) != CURLE_OK) {
	return false;
      }
    
      return true;
    }
  
    bool Curl::Read()
    {
      code = curl_easy_perform(conn);
      curl_easy_cleanup(conn);
      
      if (code != CURLE_OK) {
	return false;
      }
      
      return true;
    }

    bool Curl::IsOK()
    {
      return code == CURLE_OK;
    }

    char* Curl::Error()
    {
      return (char*)errorBuffer;
    }

    string Curl::Content()
    {
      return buffer;
    }

    Curl* Curl::Open(string url)
    {
      return new Curl(url);
    }

    // JS ...
    
    Handle<Value> Open(const Arguments &args)
    {
      HandleScope scope;

      if (args.Length() < 1) {
	return Undefined();
      }

      Handle<Value> res = Undefined();
      String::Utf8Value url(args[0]->ToString());
      Curl *handle = Curl::Open(*url);
      
      if (handle->IsOK()) {
	res = String::New(handle->Content().c_str());
      }

      return res;
    }
  }
}
