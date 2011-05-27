#include "mike/page.h"
#include "mike/utils/http.h"

namespace mike
{
  Page::Page(pFrame f, string url, string method/*="GET"*/, list<string> headers/*=()*/, string postData/*=""*/)
    : frame(f),
      url(url)
  {
    request = new http::Request(url, method);
    request->SetData(postData);

    for (list<string>::iterator it = headers.begin(); it != headers.end(); it++) {
      request->SetHeader(*it);
    }
    
    response = NULL;
  }

  Page::~Page()
  {
    if (request != NULL) delete request;
    if (response != NULL) delete response;
  }

  string Page::Url()
  {
    return url;
  }

  void Page::Load()
  {
    if (response == NULL) {
      Reload();
    }
  }

  void Page::Reload()
  {
    response = request->Perform();
  }

  bool Page::IsLoaded()
  {
    return response != NULL;
  }

  pHttpResponse Page::Response()
  {
    return response;
  }

  pHttpRequest Page::Request()
  {
    return request;
  }

  string Page::Body()
  {
    if (IsLoaded()) {
      return Response()->Body();
    } else {
      throw PageNotLoadedError();
    }
  }
}
