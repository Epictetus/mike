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
}
