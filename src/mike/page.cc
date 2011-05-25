#include "mike/page.h"

namespace mike
{
  Page::Page(pFrame f, string url)
    : frame(f),
      url(url)
  {
    //request = new RequestParams(opts);
  }

  Page::~Page()
  {
    //delete request;
  }

  string Page::Url()
  {
    return url;
  }

  void Page::Load()
  {
  }
  
  void Page::Reload()
  {
  }
}
