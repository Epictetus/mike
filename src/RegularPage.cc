#include "RegularPage.h"

namespace mike
{
  RegularPage::RegularPage(Request* request)
    : Page(request, REGULAR_PAGE)
  {
  }

  RegularPage::~RegularPage()
  {
  }

  stringstream* RegularPage::getStream()
  {
    return getResponse()->getStream();
  }

  string RegularPage::getContent()
  {
    return getResponse()->getBody();
  }
}
