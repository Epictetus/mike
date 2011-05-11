#include "mike/net.h"

namespace mike {
  namespace net
  {
    using namespace std;

    void Initialize()
    {
      curl_global_init(CURL_GLOBAL_DEFAULT);
    }
    
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

    Curl::Curl(string url, map<string,string> headers)
    {
      this->url = url;
      this->headers = headers;

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

    Curl* Curl::Open(string url, map<string,string> headers)
    {
      return new Curl(url, headers);
    }

    // JS ...

    namespace uri
    {
      Handle<Value> Open(const Arguments &args)
      {
	HandleScope scope;
	
	if (args.Length() < 1) {
	  return Undefined();
	}
	
	Handle<Value> res = Undefined();
	String::Utf8Value url(args[0]->ToString());
	map<string,string> headers;

	if (args.Length() > 1 && args[1]->IsObject()) {
	  Local<Object> _headers = args[1]->ToObject();
	  Local<Array> keys = _headers->GetPropertyNames();
	  
	  for (int i = 0; i < keys->Length(); i++) {
	    Local<Value> _key = keys->Get(i)->ToString();
	    String::Utf8Value key(_key);
	    String::Utf8Value header(_headers->Get(_key)->ToString());
	    headers[*key] = *header;
	  }
	}
	
	Curl *handle = Curl::Open(*url, headers);
	
	if (handle->IsOK()) {
	  res = String::New(handle->Content().c_str());
	}

	return res;
      }
    }
  }
}
