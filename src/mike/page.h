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
  
  class Page
  {
  private:
    string url;
    pFrame frame;
  public:
    Page(pFrame f, string url);
    ~Page();
    string Url();
    void Load();
    void Reload();
  };
}

#endif /* _MIKE_PAGE_H_ */
