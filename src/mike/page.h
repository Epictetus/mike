#ifndef _MIKE_PAGE_H_
#define _MIKE_PAGE_H_

#include <string>
#include "mike/frame.h"
#include "mike/utils/http.h"

using namespace std;

namespace mike
{
  class Frame;
  class Page;

  typedef Frame* pFrame;
  typedef Page* pPage;
  typedef http::Request* pHttpRequest;
  typedef http::Response* pHttpResponse;
  
  class Page
  {
  private:
    string url;
    pFrame frame;
    pHttpRequest request;
    pHttpResponse response;
  public:
    Page(pFrame f, string url, string method="GET", list<string> headers=list<string>(), string postData="");
    ~Page();
    string Url();
    void Load();
    void Reload();
    bool Loaded();
    pHttpRequest Request();
    pHttpResponse Response();
  };
}

#endif /* _MIKE_PAGE_H_ */
