#ifndef _MIKE_PAGE_H_
#define _MIKE_PAGE_H_

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

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

  class PageNotLoadedError
  {
  public:
    const char *ShowReason() const { return "Page not loaded"; }
  };
  
  class Page
  {
  private:
    pFrame frame;
    pHttpRequest request;
    pHttpResponse response;
    xmlDocPtr doc;
  public:
    Page(pFrame f, string url, string method="GET", list<string> headers=list<string>(), string postData="");
    ~Page();
    string Url();
    void Load();
    void Reload();
    bool IsLoaded();
    string Body();
    pHttpRequest Request();
    pHttpResponse Response();
    xmlDocPtr Document();
  };
}

#endif /* _MIKE_PAGE_H_ */
